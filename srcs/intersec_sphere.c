/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 01:41:08 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/24 01:41:31 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersec_sphere(t_sphere *sphere, t_vector coords, t_vector direction)
{
	float		d;
	float		k[3];
	float		t[2];
	t_vector	*oc;

	oc = subtract_vect(coords, *sphere->coords);
	k[0] = scal_mult_vec(direction, direction);
	k[1] = 2 * scal_mult_vec(*oc, direction);
	k[2] = scal_mult_vec(*oc, *oc) - sphere->radius * sphere->radius;
	d = pow(k[1], 2) - 4 * k[0] * k[2];
	free(oc);
	if (d < 0)
		return (0);
	t[0] = (-k[1] + sqrt(d)) / 2 * k[0];
	t[1] = (-k[1] - sqrt(d)) / 2 * k[0];
	if (t[0] < t[1])
		return (t[0]);
	return (t[1]);
}
