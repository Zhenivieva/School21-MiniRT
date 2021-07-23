/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 23:03:23 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/21 23:03:45 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plight2(t_scene **scene, char *stroka, float coord[3], float bright)
{
	int rgb[3];
	int i;

	i = -1;
	while (++i < 3)
	{
		if ((rgb[i] = get_int(&stroka)) < 0 || rgb[i] > 255)
			print_errors(-2);
		if ((i < 2) && *stroka != ',')
			print_errors(-2);
		(*stroka == ',') ? (stroka++) : 0;
	}
	return (!(lstadd_back(&(*scene)->lights, new_light(1,
new_vector(coord[0], coord[1], coord[2]), bright,
new_vector(rgb[0], rgb[1], rgb[2])), 5, -1)) ? 0 : -1);
}

int	parse_plight(t_scene **scene, char *stroka)
{
	float	coord[3];
	float	bright;
	int		i;

	stroka++;
	move_by_space(&stroka);
	i = -1;
	while (++i < 3)
	{
		coord[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	move_by_space(&stroka);
	bright = (float)get_int(&stroka);
	if ((bright = get_mantfloat(&stroka, bright)) < 0 || bright > 1)
		print_errors(-2);
	(*scene)->sum_bright += bright;
	move_by_space(&stroka);
	return (parse_plight2(scene, stroka, coord, bright));
}
