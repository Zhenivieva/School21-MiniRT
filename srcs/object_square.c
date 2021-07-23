/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 03:03:31 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 23:49:57 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		set_points_norm(t_square **square)
{
	t_vector	*points[4];
	int			i;

	points[0] = new_vector((*square)->size / 2, (*square)->size / 2, 0);
	points[1] = new_vector(-(*square)->size / 2, (*square)->size / 2, 0);
	points[2] = new_vector((*square)->size / 2, -(*square)->size / 2, 0);
	points[3] = new_vector(-(*square)->size / 2, -(*square)->size / 2, 0);
	i = -1;
	while (++i < 4)
		rot_v1_v2(points[i], (*square)->dir);
	(*square)->a = add_vect(*points[0], *(*square)->coords);
	(*square)->b = add_vect(*points[1], *(*square)->coords);
	(*square)->c = add_vect(*points[2], *(*square)->coords);
	(*square)->d = add_vect(*points[3], *(*square)->coords);
	(*square)->ab = subtract_vect(*(*square)->b, *(*square)->a);
	(*square)->ac = subtract_vect(*(*square)->c, *(*square)->a);
	(*square)->dir = cross_vect(*(*square)->ab, *(*square)->ac);
	i = -1;
	while (++i < 4)
		free(points[i]);
}

t_square	*new_square(t_vector *coords, t_vector *dir, float size,
t_vector *col)
{
	t_square *square;

	if (!(square = malloc(sizeof(t_square))))
		print_errors(-6);
	square->coords = coords;
	square->dir = dir;
	square->size = size;
	square->color = col;
	set_points_norm(&square);
	square->gloss = -1;
	return (square);
}
