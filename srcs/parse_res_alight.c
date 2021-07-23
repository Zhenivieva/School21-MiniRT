/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_res_alight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:24:46 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/16 19:24:49 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_resolution(t_scene **scene, char *stroka)
{
	long int resx;
	long int resy;

	stroka++;
	move_by_space(&stroka);
	if ((resx = get_int(&stroka)) <= 0)
		return (-1);
	move_by_space(&stroka);
	if ((resy = get_int(&stroka)) <= 0)
		return (-1);
	check_end_of_str(&stroka);
	return (!((*scene)->vport = new_canvas(resx, resy, 1)) ? -1 : 0);
}

int		parse_alight(t_scene **scene, char *stroka)
{
	int			rgb[3];
	t_vector	*color;
	int			i;

	stroka++;
	move_by_space(&stroka);
	(*scene)->sum_bright = (float)get_int(&stroka);
	if (((*scene)->sum_bright = get_mantfloat(&stroka,
(*scene)->sum_bright)) < 0 || (*scene)->sum_bright > 1)
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
	check_end_of_str(&stroka);
	color = new_vector(rgb[0], rgb[1], rgb[2]);
	return (!(lstadd_back(&(*scene)->lights, new_light(0, new_vector(0,
0, 0), (*scene)->sum_bright, color), 5, -1)) ? 0 : -1);
}
