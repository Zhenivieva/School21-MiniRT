/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:30:16 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:30:19 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*color_int_to_vect(unsigned int color)
{
	int r;
	int g;
	int b;

	b = (int)(color % 256);
	g = (int)(((color - b) / 256) % 256);
	r = (int)(((color - b) / 65536) - g / 256);
	return (new_vector((float)r, (float)g, (float)b));
}

int			color_vect_to_int(t_vector *color)
{
	return ((((((int)color->x) << 8) + (int)color->y) << 8) + (int)color->z);
}

void		set_maxmin_color(t_vector *color)
{
	color->x < 0 ? color->x = 0 : 0;
	color->x > 255 ? color->x = 255 : 0;
	color->y < 0 ? color->y = 0 : 0;
	color->y > 255 ? color->y = 255 : 0;
	color->z < 0 ? color->z = 0 : 0;
	color->z > 255 ? color->z = 255 : 0;
}

void		normalise_vect(t_vector *vector)
{
	float length;

	length = length_vec(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

t_vector	*get_normalised_vect(t_vector *vec)
{
	float len;

	len = length_vec(*vec);
	return (new_vector(vec->x / len, vec->y / len, vec->z / len));
}
