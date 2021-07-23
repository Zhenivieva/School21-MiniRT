/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:04:53 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 19:04:57 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				calc_color_with_light(t_lstobj *closest_obj, t_vector direction,
float closest_t, t_scene *scene)
{
	int			color;
	t_vector	*temp;
	t_vector	l_vectors[3];

	color = 0;
	temp = mult_vect(direction, closest_t);
	l_vectors[0] = add_vvect(*((t_camera *)scene->cams->obj)->coords, *temp);
	free(temp);
	l_vectors[1] = (t_vector){0, 0, 0};
	l_vectors[2] = (t_vector){direction.x * (-1),
direction.y * (-1), direction.z * (-1)};
	color = compute_lightning(l_vectors, scene->lights, scene, closest_obj);
	if (scene->depth > 0 && closest_obj->reflective > 0)
		color = color_with_reflect(closest_obj, scene, l_vectors, color);
	return (color);
}

t_lstobj		*closest_obj_intersect(t_vector coords, t_vector direction,
t_scene *scene, float *closest_t)
{
	float		t_temp;
	t_lstobj	*objects;
	t_lstobj	*closest_obj;

	closest_obj = NULL;
	*closest_t = -1;
	objects = scene->objs;
	while (objects)
	{
		t_temp = get_intersec(coords, direction, objects);
		if (t_temp > scene->t_min && (t_temp < scene->t_max ||
scene->t_max == -1) && (t_temp < *closest_t || *closest_t == -1))
		{
			*closest_t = t_temp;
			closest_obj = objects;
		}
		scene->t_max = -1;
		objects = objects->next;
	}
	return (closest_obj);
}

int				raytraycing(t_vector direction, t_scene *scene)
{
	float		closest_t;
	t_lstobj	*closest_obj;
	int			color;

	color = 0;
	if (!(closest_obj = closest_obj_intersect(*(((t_camera *)scene->cams->obj)
->coords), direction, scene, &closest_t)))
		return (scene->background_color);
	color = calc_color_with_light(closest_obj, direction, closest_t, scene);
	return (color);
}
