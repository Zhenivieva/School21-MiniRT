/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:30:16 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:30:19 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*cross_vect(t_vector v1, t_vector v2)
{
	return (new_vector(v1.y * v2.z - v1.z * v2.y,
v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x));
}

t_vector	*add_vect(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	*subtract_vect(t_vector v1, t_vector v2)
{
	return (new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector	*mult_vect(t_vector v1, float t)
{
	return (new_vector(v1.x * t, v1.y * t, v1.z * t));
}

t_vector	add_vvect(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
