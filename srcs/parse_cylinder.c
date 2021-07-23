/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 03:04:04 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/30 03:04:08 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cylinder2(t_scene **scene, char *stroka, float coord[3], float dir[3])
{
	float	param[2];
	int		rgb[3];
	int		i;

	move_by_space(&stroka);
	if ((param[0] = get_mantfloat(&stroka, (float)get_int(&stroka))) <= 0)
		print_errors(-2);
	move_by_space(&stroka);
	if ((param[1] = get_mantfloat(&stroka, (float)get_int(&stroka))) <= 0)
		print_errors(-2);
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
	return (!(lstadd_back(&(*scene)->objs, new_cylinder(new_vector(coord[0],
coord[1], coord[2]), new_vector(dir[0], dir[1], dir[2]), param,
new_vector(rgb[0], rgb[1], rgb[2])), 4, -1)) ? 0 : -1);
}

int	parse_cylinder(t_scene **scene, char *stroka)
{
	float	coord[3];
	float	dir[3];
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
	i = -1;
	while (++i < 3)
	{
		dir[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	(pow(dir[0], 2) + pow(dir[1], 2) + pow(dir[2], 2) == 0) ? dir[2] = 1 : 0;
	return (parse_cylinder2(scene, stroka, coord, dir));
}
