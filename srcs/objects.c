/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 23:49:37 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 23:49:40 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	*new_sphere(t_vector *coords, float radius, t_vector *color)
{
	t_sphere *sphere;

	if (!(sphere = malloc(sizeof(t_sphere))))
		print_errors(-6);
	sphere->coords = coords;
	sphere->color = color;
	sphere->radius = radius;
	sphere->gloss = 10;
	return (sphere);
}

t_plane		*new_plane(t_vector *coords, t_vector *dir, t_vector *color)
{
	t_plane *plane;

	if (!(plane = malloc(sizeof(t_square))))
		print_errors(-6);
	plane->coords = coords;
	plane->dir = dir;
	plane->color = color;
	plane->gloss = -1;
	return (plane);
}

t_trian		*new_trian(t_vector *a, t_vector *b, t_vector *c, t_vector *col)
{
	t_trian *trian;

	if (!(trian = malloc(sizeof(t_trian))))
		print_errors(-6);
	trian->a = a;
	trian->b = b;
	trian->c = c;
	trian->color = col;
	trian->gloss = -1;
	trian->ab = subtract_vect(*b, *a);
	trian->ac = subtract_vect(*c, *a);
	trian->normal = cross_vect(*trian->ab, *trian->ac);
	trian->abIab = scal_mult_vec(*trian->ab, *trian->ab);
	trian->abIac = scal_mult_vec(*trian->ab, *trian->ac);
	trian->acIac = scal_mult_vec(*trian->ac, *trian->ac);
	trian->d = trian->abIac * trian->abIac - trian->abIab * trian->acIac;
	return (trian);
}

t_cylinder	*new_cylinder(t_vector *coords, t_vector *dir, float param[2],
t_vector *col)
{
	t_cylinder	*cyl;

	if (!(cyl = malloc(sizeof(t_cylinder))))
		print_errors(-6);
	cyl->coords = coords;
	cyl->dir = dir;
	cyl->diametr = param[0];
	cyl->height = param[1];
	cyl->color = col;
	cyl->gloss = 10;
	normalise_vect(cyl->dir);
	cyl->point1 = add_vect(*cyl->coords, (t_vector){param[1] / 2 *
dir->x, param[1] / 2 * dir->y, param[1] / 2 * dir->z});
	cyl->point2 = add_vect(*cyl->coords, (t_vector){-param[1] / 2 *
dir->x, -param[1] / 2 * dir->y, -param[1] / 2 * dir->z});
	return (cyl);
}
