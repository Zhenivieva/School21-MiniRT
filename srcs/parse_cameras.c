/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 19:24:05 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/16 19:24:13 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cam2(t_scene **scene, char *stroka, float coord[3], float vect_dir[3])
{
	int			fov;
	t_vector	*temp;
	t_vector	*temp2;

	move_by_space(&stroka);
	((fov = get_int(&stroka)) <= 0 || fov > 180) ? print_errors(-2) : 0;
	check_end_of_str(&stroka);
	temp = new_vector(vect_dir[0], vect_dir[1], vect_dir[2]);
	temp2 = get_normalised_vect(temp);
	free(temp);
	return (!(lstadd_back(&(*scene)->cams, new_camera(new_vector(
coord[0], coord[1], coord[2]), temp2, fov), 6, -1)) ? 0 : -1);
}

int	parse_cam(t_scene **scene, char *stroka)
{
	float	coord[3];
	float	vect_dir[3];
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
	i = -1;
	while (++i < 3)
	{
		vect_dir[i] = get_mantfloat(&stroka, (float)get_int(&stroka));
		((i < 2) && *stroka != ',') ? print_errors(-2) : 0;
		(*stroka == ',') ? (stroka++) : 0;
	}
	(pow(vect_dir[0], 2) + pow(vect_dir[1], 2) + pow(vect_dir[2], 2) == 0) ?
vect_dir[2] = 1 : 0;
	return (parse_cam2(scene, stroka, coord, vect_dir));
}
