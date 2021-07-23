/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shiny.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:29:33 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 19:29:36 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		calcul_shiny(t_vector *l_vectors, t_light *light, t_vector *vec_l,
float gloss)
{
	float		r_dot_v;
	t_vector	*vec_r;
	t_vector	*temp;
	float		bright;
	float		length_v;

	length_v = length_vec(l_vectors[2]);
	bright = 0;
	temp = mult_vect(l_vectors[1], 2.0 * scal_mult_vec(l_vectors[1],
*vec_l));
	vec_r = subtract_vect(*temp, *vec_l);
	free(temp);
	r_dot_v = scal_mult_vec(*vec_r, l_vectors[2]);
	if (r_dot_v > 0)
		bright += light->bright * pow(r_dot_v / (length_vec(*vec_r) * length_v),
gloss);
	free(vec_r);
	return (bright);
}

t_vector	*get_color(t_lstobj *objects)
{
	if (objects->type == 0)
		return (((t_sphere *)objects->obj)->color);
	if (objects->type == 1)
		return (((t_plane *)objects->obj)->color);
	if (objects->type == 2)
		return (((t_square *)objects->obj)->color);
	if (objects->type == 3)
		return (((t_trian *)objects->obj)->color);
	if (objects->type == 4)
		return (((t_cylinder *)objects->obj)->color);
	return (NULL);
}
