/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:28:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 17:28:54 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersec_triangle(t_trian *trian, t_vector coords, t_vector direction)
{
	float		k[6];
	float		t;
	t_vector	*coord_p;
	t_vector	*ray;
	t_vector	*ap;

	if (!(k[0] = scal_mult_vec(direction, *trian->normal)))
		return (0);
	if ((t = -(scal_mult_vec(coords, *trian->normal) -
(scal_mult_vec(*trian->normal, *trian->a))) / k[0]) < 0)
		return (0);
	ray = mult_vect(direction, t);
	coord_p = add_vect(coords, *ray);
	free(ray);
	ap = subtract_vect(*coord_p, *trian->a);
	k[1] = scal_mult_vec(*ap, *trian->ab);
	k[2] = scal_mult_vec(*ap, *trian->ac);
	k[3] = (trian->abIac * k[2] - trian->acIac * k[1]) / trian->d;
	k[4] = (trian->abIac * k[1] - trian->abIab * k[2]) / trian->d;
	free(coord_p);
	free(ap);
	if (k[3] < 0 || k[3] > 1 || k[4] < 0 || (k[3] + k[4] > 1))
		return (0);
	return (t);
}
