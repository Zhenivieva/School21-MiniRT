/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 03:06:59 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/30 03:07:06 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rot_x(t_vector *v1, float a)
{
	t_vector v2;

	v2.x = v1->x;
	v2.y = v1->y * cos(a) - v1->z * sin(a);
	v2.z = v1->y * sin(a) + v1->z * cos(a);
	*v1 = v2;
}

void	rot_y(t_vector *v1, float a)
{
	t_vector	v2;

	v2.x = v1->x * cos(a) + v1->z * sin(a);
	v2.y = v1->y;
	v2.z = -v1->x * sin(a) + v1->z * cos(a);
	*v1 = v2;
}

void	rot_z(t_vector *v1, float a)
{
	t_vector	v2;

	v2.x = v1->x * cos(a) - v1->y * sin(a);
	v2.y = v1->x * sin(a) + v1->y * cos(a);
	v2.z = v1->z;
	*v1 = v2;
}

void	rot_v1_v2(t_vector *v1, t_vector *vec_angle)
{
	rot_x(v1, vec_angle->x);
	rot_y(v1, vec_angle->y);
	rot_z(v1, vec_angle->z);
}
