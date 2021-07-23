/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:00:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 16:00:41 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_intersec(t_vector coords, t_vector direction, t_lstobj *object)
{
	float t;

	t = 0;
	if (object->type == 0)
		t = intersec_sphere(object->obj, coords, direction);
	else if (object->type == 1)
		t = intersec_plane(object->obj, coords, direction);
	else if (object->type == 2)
		t = intersec_square(object->obj, coords, direction);
	else if (object->type == 3)
		t = intersec_triangle(object->obj, coords, direction);
	else if (object->type == 4)
		t = intersec_cylinder(object->obj, coords, direction);
	return (t);
}
