/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:30:16 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/25 21:25:47 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*new_vector(float x, float y, float z)
{
	t_vector *vector;

	if (!(vector = malloc(sizeof(t_vector))))
		print_errors(-6);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	ft_lstadd_front(&g_mem, ft_lstnew(vector));
	return (vector);
}

t_vector	*copy_vector(t_vector *v1)
{
	return (new_vector(v1->x, v1->y, v1->z));
}

float		scal_mult_vec(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float		length_vec(t_vector vector)
{
	return (sqrt(pow(vector.x, 2) + (pow(vector.y, 2) + (pow(vector.z, 2)))));
}

float		dist_vec(t_vector v1, t_vector v2)
{
	return (sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) +
pow(v2.z - v1.z, 2)));
}
