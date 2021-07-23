/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:50:44 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 16:50:47 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersec_square(t_square *sqr, t_vector coords, t_vector direction)
{
	float		k[4];
	float		t;
	t_vector	*coord_p;
	t_vector	*ray;
	t_vector	*ap;

	k[0] = scal_mult_vec(coords, *sqr->dir) - (scal_mult_vec(*sqr->dir,
*sqr->coords));
	if (!(k[1] = scal_mult_vec(direction, *sqr->dir)))
		return (0);
	if ((t = -k[0] / k[1]) <= 0)
		return (0);
	ray = mult_vect(direction, t);
	coord_p = add_vect(coords, *ray);
	free(ray);
	ap = subtract_vect(*coord_p, *sqr->a);
	k[2] = scal_mult_vec(*ap, *sqr->ab) / scal_mult_vec(*sqr->ab, *sqr->ab);
	k[3] = scal_mult_vec(*ap, *sqr->ac) / scal_mult_vec(*sqr->ac, *sqr->ac);
	free(ap);
	free(coord_p);
	if (k[2] >= 0 && k[2] <= 1 && k[3] >= 0 && k[3] <= 1)
		return (t);
	return (0);
}
