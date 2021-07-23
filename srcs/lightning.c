/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 22:11:41 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 22:11:44 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*type_light(t_params *params, t_light *light)
{
	t_vector *vec_l;

	vec_l = NULL;
	if (light->type == 1)
	{
		vec_l = subtract_vect(*light->coords, *params->l_vectors[0]);
		params->scene->t_max = 1;
	}
	else if (light->type == 2)
	{
		vec_l = light->coords;
		params->scene->t_max = -1;
	}
	params->scene->t_min = 0.001;
	return (vec_l);
}

void		calculate_normal(t_params *params, t_light *light,
t_lstobj *objects)
{
	void *object;

	object = objects->obj;
	if (objects->type == 0)
		check_light_intersec_sphere(*params->l_vectors, object);
	else if (objects->type == 1)
		check_light_intersec_plane(*params->l_vectors, object, light);
	else if (objects->type == 2)
		check_light_intersec_square(*params->l_vectors, object, light);
	else if (objects->type == 3)
		check_light_intersec_triangle(*params->l_vectors, object, light);
	else if (objects->type == 4)
		check_light_intersec_cyl(params, object, light);
}

float		compute_special_lights(t_params *params, t_light *light,
t_lstobj *objects)
{
	float		i_n_dot_l[2];
	t_vector	*vec_l;
	t_lstobj	*shadow_obj;
	float		closest_t;

	i_n_dot_l[0] = 0;
	vec_l = type_light(params, light);
	if (!(shadow_obj = closest_obj_intersect(*params->l_vectors[0],
*vec_l, params->scene, &closest_t)))
	{
		calculate_normal(params, light, objects);
		i_n_dot_l[1] = scal_mult_vec(*params->l_vectors[1], *vec_l);
		if (i_n_dot_l[1] > 0)
		{
			i_n_dot_l[0] += ((light->bright * i_n_dot_l[1]) /
((length_vec(*params->l_vectors[1]) * length_vec(*vec_l))));
		}
		if (params->gloss != -1)
			i_n_dot_l[0] += calcul_shiny(*params->l_vectors, light, vec_l,
params->gloss);
	}
	if (light->type == 1)
		free(vec_l);
	return (i_n_dot_l[0]);
}

float		get_gloss(t_lstobj *objects)
{
	if (objects->type == 0)
		return (((t_sphere *)objects->obj)->gloss);
	if (objects->type == 4)
		return (((t_cylinder *)objects->obj)->gloss);
	else
		return (-1);
}

int			compute_lightning(t_vector *l_vectors, t_lstobj *lights,
t_scene *scene, t_lstobj *objects)
{
	float		bright;
	int			ret_color;
	t_params	params;

	params.gloss = get_gloss(objects);
	params.l_vectors[0] = l_vectors;
	params.l_vectors[1] = l_vectors + 1;
	params.l_vectors[2] = l_vectors + 2;
	params.scene = scene;
	params.color[3] = get_color(objects);
	params.color[2] = new_vector(0, 0, 0);
	while (lights)
	{
		bright = 0;
		if (((t_light *)lights->obj)->type == 0)
			set_color_ambient(params.color, &bright, lights);
		else
			set_color_special_lights(&bright, &params, objects, lights);
		params.color[2] = copy_vector(params.color[0]);
		free(params.color[0]);
		lights = lights->next;
	}
	ret_color = color_vect_to_int(params.color[2]);
	free(params.color[2]);
	return (ret_color);
}
