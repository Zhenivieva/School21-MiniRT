/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:14:14 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 16:14:17 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	check_top_plane(t_cylinder *cyl, t_vector coords, t_vector direction)
{
	float		t;
	float		a;
	float		b;
	t_vector	*temp;
	t_vector	*point;

	a = scal_mult_vec(coords, *cyl->dir) - (scal_mult_vec(*cyl->dir,
*cyl->point2));
	b = scal_mult_vec(direction, *cyl->dir);
	if (!b)
		return (0);
	t = -a / b;
	temp = mult_vect(direction, t);
	point = add_vect(coords, *temp);
	a = dist_vec(*point, *cyl->point2);
	free(temp);
	free(point);
	return (((t > 0) && (a < cyl->diametr / 2)) ? t : 0);
}

float	check_bottom_plane(t_cylinder *cyl, t_vector coords, t_vector direction)
{
	float		t;
	float		a;
	float		b;
	t_vector	*temp;
	t_vector	*point;

	a = scal_mult_vec(coords, *cyl->dir) - (scal_mult_vec(*cyl->dir,
*cyl->point1));
	b = scal_mult_vec(direction, *cyl->dir);
	if (!b)
		return (0);
	t = -a / b;
	temp = mult_vect(direction, t);
	point = add_vect(coords, *temp);
	a = dist_vec(*point, *cyl->point1);
	free(temp);
	free(point);
	return (((t > 0) && (a < cyl->diametr / 2)) ? t : check_top_plane(cyl,
coords, direction));
}

float	check_cyl_side(float t, t_cylinder *cyl, t_vector coords,
t_vector direction)
{
	t_vector	*temp;
	t_vector	*xp1;
	t_vector	*point;
	float		a1;
	float		a2;

	temp = mult_vect(direction, t);
	point = add_vect(coords, *temp);
	free(temp);
	xp1 = subtract_vect(*cyl->point1, *point);
	a1 = sqrt(pow(length_vec(*xp1), 2) - pow(cyl->diametr, 2) / 4);
	free(xp1);
	xp1 = subtract_vect(*cyl->point2, *point);
	a2 = sqrt(pow(length_vec(*xp1), 2) - pow(cyl->diametr, 2) / 4);
	free(point);
	free(xp1);
	if (a1 <= cyl->height && a2 <= cyl->height)
		return (t);
	else
		return (check_bottom_plane(cyl, coords, direction));
}

float	intersec_cylinder(t_cylinder *cyl, t_vector coords, t_vector direction)
{
	float		dis;
	float		t[2];
	float		ret;
	t_vector	*dif;
	float		k[5];

	dif = subtract_vect(coords, *cyl->coords);
	k[0] = scal_mult_vec(*cyl->dir, *dif);
	k[1] = scal_mult_vec(direction, *cyl->dir);
	k[2] = scal_mult_vec(direction, direction) - pow(k[1], 2);
	k[3] = 2 * (scal_mult_vec(direction, *dif) - k[1] * k[0]);
	k[4] = scal_mult_vec(*dif, *dif) - pow(k[0], 2) - pow(cyl->diametr / 2, 2);
	if ((dis = pow(k[3], 2) - 4 * k[2] * k[4]) < 0)
		return (0);
	t[0] = (-k[3] + sqrt(dis)) / (2 * k[2]);
	t[1] = (-k[3] - sqrt(dis)) / (2 * k[2]);
	ret = t[0] < t[1] ? t[0] : t[1];
	free_and_null((void **)&dif);
	return (check_cyl_side(ret, cyl, coords, direction));
}
