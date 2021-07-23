/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:04:27 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/21 23:06:50 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere2(t_scene **scene, char *stroka, float coord[3], float diametr)
{
	int rgb[3];
	int i;

	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		if ((rgb[i] = get_int(&stroka)) < 0 || rgb[i] > 255)
			print_errors(-2);
		if ((i < 2) && *stroka != ',')
			print_errors(-2);
		(*stroka == ',') ? (stroka++) : 0;
	}
	return (!(lstadd_back(&(*scene)->objs, new_sphere(new_vector(coord[0],
coord[1], coord[2]), diametr / 2, new_vector(rgb[0],
rgb[1], rgb[2])), 0, 0.5)) ? 0 : -1);
}

int	parse_sphere(t_scene **scene, char *stroka)
{
	float	coord[3];
	float	diametr;
	int		i;

	stroka = stroka + 2;
	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		coord[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	move_by_space(&stroka);
	if ((diametr = get_mantfloat(&stroka, (float)get_int(&stroka))) <= 0)
		print_errors(-2);
	return (parse_sphere2(scene, stroka, coord, diametr));
}
