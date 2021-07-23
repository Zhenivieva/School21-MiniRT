/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:40:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 16:40:42 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersec_plane(t_plane *object, t_vector coords, t_vector direction)
{
	float t;
	float a;
	float b;

	a = scal_mult_vec(coords, *object->dir) - (scal_mult_vec(*object->dir,
*object->coords));
	b = scal_mult_vec(direction, *object->dir);
	if (!b)
		return (0);
	t = -a / b;
	return ((t > 0) ? t : 0);
}
