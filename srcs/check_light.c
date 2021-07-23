/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:07 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 15:09:13 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_light_intersec_sphere(t_vector *l_vectors, void *object)
{
	t_vector *temp;
	t_vector *temp2;

	temp = subtract_vect(l_vectors[0], *(((t_sphere *)object)->coords));
	temp2 = mult_vect(*temp, 1 / length_vec(*temp));
	l_vectors[1] = *temp2;
	free(temp);
	free(temp2);
}

void	check_light_intersec_plane(t_vector *l_vectors, void *object,
t_light *light)
{
	float		k[4];
	t_vector	*temp[3];
	float		denom;
	float		t;

	temp[1] = mult_vect(*((t_plane *)object)->dir, -1);
	denom = -(scal_mult_vec(*((t_plane *)object)->dir,
*((t_plane *)object)->coords));
	k[0] = scal_mult_vec(*light->coords, *((t_plane *)object)->dir) + denom;
	k[1] = scal_mult_vec(*temp[1], *((t_plane *)object)->dir);
	t = -k[0] / k[1];
	temp[2] = mult_vect(*temp[1], t);
	free(temp[1]);
	temp[0] = add_vect(*light->coords, *temp[2]);
	free(temp[2]);
	temp[2] = subtract_vect(*light->coords, *temp[0]);
	l_vectors[1] = *mult_vect(*temp[2], 1 / length_vec(*temp[2]));
	free(temp[2]);
	free(temp[0]);
}

void	check_light_intersec_triangle(t_vector *l_vectors, void *object,
t_light *light)
{
	t_vector	*v[6];
	float		k[4];
	float		t;

	v[1] = subtract_vect(*((t_trian *)object)->b, *((t_trian *)object)->a);
	v[2] = subtract_vect(*((t_trian *)object)->c, *((t_trian *)object)->a);
	v[0] = cross_vect(*v[1], *v[2]);
	v[3] = mult_vect(*v[0], -1);
	k[0] = scal_mult_vec(*light->coords, *v[0]) - (scal_mult_vec((*v[0]),
*((t_trian *)object)->a));
	k[1] = scal_mult_vec(*v[3], *v[0]);
	free(v[0]);
	free(v[1]);
	free(v[2]);
	t = -k[0] / k[1];
	v[5] = mult_vect(*v[3], t);
	free(v[3]);
	v[4] = add_vect(*light->coords, *v[5]);
	free(v[5]);
	v[5] = subtract_vect(*light->coords, *v[4]);
	l_vectors[1] = *mult_vect(*v[5], 1 / length_vec(*v[5]));
	free(v[5]);
	free(v[4]);
}

void	check_light_intersec_square(t_vector *l_vectors, void *object,
t_light *light)
{
	t_vector	*temp2;
	float		k[4];
	t_vector	*point;
	t_vector	*temp;
	float		t;

	temp2 = mult_vect(*((t_square *)object)->dir, -1);
	k[0] = scal_mult_vec(*light->coords, *((t_square *)object)->dir) -
(scal_mult_vec(*((t_square *)object)->dir, *((t_square *)object)->coords));
	k[1] = scal_mult_vec(*temp2, *((t_square *)object)->dir);
	t = -k[0] / k[1];
	temp = mult_vect(*temp2, t);
	point = add_vect(*light->coords, *temp);
	free(temp);
	temp = subtract_vect(*light->coords, *point);
	l_vectors[1] = *mult_vect(*temp, 1 / length_vec(*temp));
	free(temp);
	free(point);
}
