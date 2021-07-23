/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 18:57:36 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 18:57:39 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*reflect_ray(t_vector v1, t_vector v2)
{
	t_vector *v_temp;
	t_vector *new;

	v_temp = mult_vect(v2, 2 * scal_mult_vec(v1, v2));
	new = subtract_vect(*v_temp, v1);
	free(v_temp);
	return (new);
}

int			color_with_reflect(t_lstobj *closest_object, t_scene *scene,
t_vector *l_vectors, int color)
{
	t_vector *temp;
	t_vector *temp2;
	t_vector *reflect_color;

	temp = reflect_ray(l_vectors[2], l_vectors[1]);
	temp2 = color_int_to_vect(color);
	((t_camera *)scene->cams->obj)->coords = &l_vectors[0];
	scene->depth--;
	color = raytraycing(*temp, scene);
	free(temp);
	temp = mult_vect(*temp2, 1 - closest_object->reflective);
	free(temp2);
	reflect_color = color_int_to_vect(color);
	temp2 = mult_vect(*reflect_color, closest_object->reflective);
	free(reflect_color);
	reflect_color = add_vect(*temp, *temp2);
	free(temp);
	free(temp2);
	set_maxmin_color(reflect_color);
	color = color_vect_to_int(reflect_color);
	free(reflect_color);
	return (color);
}
