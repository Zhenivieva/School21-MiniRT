/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:09:31 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 15:09:35 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check(t_vector *l_vectors, void *cyl, t_light *light)
{
	t_vector	*temp[2];
	t_vector	*point;
	float		k[4];
	float		t;

	temp[0] = mult_vect(*((t_plane *)cyl)->dir, -1);
	k[0] = scal_mult_vec(*light->coords, *((t_plane *)cyl)->dir) -
			(scal_mult_vec(*((t_plane *)cyl)->dir, *((t_plane *)cyl)->coords));
	k[1] = scal_mult_vec(*temp[0], *((t_plane *)cyl)->dir);
	t = -k[0] / k[1];
	temp[1] = mult_vect(*temp[0], t);
	free(temp[0]);
	point = add_vect(*light->coords, *temp[1]);
	free(temp[1]);
	temp[1] = subtract_vect(*light->coords, *point);
	normalise_vect(temp[1]);
	l_vectors[1] = *temp[1];
	free(temp[1]);
	free(point);
}

void	check_bottom(t_params *params, void *cyl, t_light *light,
t_vector direction)
{
	t_vector	*temp;
	t_vector	*point;
	float		k[4];

	k[0] = scal_mult_vec(*((t_camera *)params->scene->cams->obj)->coords,
	*((t_cylinder *)cyl)->dir) - (scal_mult_vec(*((t_cylinder *)cyl)->dir,
	*((t_cylinder *)cyl)->point1));
	k[1] = scal_mult_vec(direction, *((t_cylinder *)cyl)->dir);
	if ((k[2] = -k[0] / k[1]) > 0)
	{
		temp = mult_vect(direction, k[2]);
		point = add_vect(*((t_camera *)params->scene->cams->obj)->coords,
*temp);
		free(temp);
		k[0] = dist_vec(*point, *((t_cylinder *)cyl)->point1);
		free(point);
		if (k[0] < ((t_cylinder *)cyl)->diametr / 2)
			check(*params->l_vectors, cyl, light);
	}
}

void	check_top(t_params *params, void *cyl, t_light *light,
t_vector direction)
{
	t_vector	*temp[2];
	float		k[4];

	k[0] = scal_mult_vec(*((t_camera *)params->scene->cams->obj)->coords,
	*((t_cylinder *)cyl)->dir) - (scal_mult_vec(*((t_cylinder *)cyl)->dir,
	*((t_cylinder *)cyl)->point2));
	k[1] = scal_mult_vec(direction, *((t_cylinder *)cyl)->dir);
	if ((k[2] = -k[0] / k[1]) > 0)
	{
		temp[0] = mult_vect(direction, k[2]);
		temp[1] = add_vect(*((t_camera *)params->scene->cams->obj)->coords,
*temp[0]);
		free(temp[0]);
		k[0] = dist_vec(*temp[1], *((t_cylinder *)cyl)->point2);
		free(temp[1]);
		if (k[0] < ((t_cylinder *)cyl)->diametr / 2)
			check(*params->l_vectors, cyl, light);
	}
}

void	check_light_intersec_cyl(t_params *params, void *cyl, t_light *light)
{
	t_vector	*temp1;
	t_vector	*direction;

	direction = mult_vect(*params->l_vectors[2], -1);
	temp1 = subtract_vect(*params->l_vectors[0],
*(((t_cylinder *)cyl)->coords));
	*params->l_vectors[1] = *mult_vect(*temp1, 1 / length_vec(*temp1));
	free(temp1);
	if (scal_mult_vec(*((t_cylinder *)cyl)->dir, *direction) < 0)
		check_bottom(params, cyl, light, *direction);
	else if (scal_mult_vec(*((t_cylinder *)cyl)->dir, *direction) > 0)
		check_top(params, cyl, light, *direction);
	free(direction);
}
