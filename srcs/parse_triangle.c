/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 03:06:05 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/30 03:06:08 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_triangle2(t_scene **scene, char *stroka, float crd1[3], float crd2[3])
{
	float	crd3[3];
	int		rgb[3];
	int		i;

	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		crd3[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		if ((rgb[i] = get_int(&stroka)) < 0 || rgb[i] > 255)
			print_errors(-2);
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	return (!(lstadd_back(&(*scene)->objs, new_trian(new_vector(
crd1[0], crd1[1], crd1[2]), new_vector(crd2[0], crd2[1], crd2[2]),
new_vector(crd3[0], crd3[1], crd3[2]), new_vector(rgb[0], rgb[1], rgb[2])),
3, -1)) ? 0 : -1);
}

int	parse_triangle(t_scene **scene, char *stroka)
{
	float	crd1[3];
	float	crd2[3];
	int		i;

	stroka = stroka + 2;
	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		crd1[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		crd2[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	return (parse_triangle2(scene, stroka, crd1, crd2));
}
