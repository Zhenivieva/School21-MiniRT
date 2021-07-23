/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:55:07 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/25 21:38:59 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_string(t_scene **scene, char *stroka)
{
	if (stroka[0] == '\0')
		return (0);
	else if (stroka[0] == 'R')
		return (parse_resolution(scene, stroka));
	else if (stroka[0] == 'A')
		return (parse_alight(scene, stroka));
	else if (stroka[0] == 'l')
		return (parse_plight(scene, stroka));
	else if (stroka[0] == 'c' && stroka[1] == 'y')
		return (parse_cylinder(scene, stroka));
	else if (stroka[0] == 'c')
		return (parse_cam(scene, stroka));
	else if (stroka[0] == 's' && stroka[1] == 'p')
		return (parse_sphere(scene, stroka));
	else if (stroka[0] == 's' && stroka[1] == 'q')
		return (parse_square(scene, stroka));
	else if (stroka[0] == 'p' && stroka[1] == 'l')
		return (parse_plane(scene, stroka));
	else if (stroka[0] == 't' && stroka[1] == 'r')
		return (parse_triangle(scene, stroka));
	else
		return (-1);
}

void	set_viewplane(t_scene **scene)
{
	float pl_wid;
	float wh_ratio;

	pl_wid = 2 * tan((((t_camera *)(*scene)->cams->obj)->fov) * M_PI / 360);
	wh_ratio = (*scene)->vport->width / (*scene)->vport->height;
	if (!(*scene)->vport)
		print_errors(-2);
	(*scene)->vplane = new_canvas(pl_wid, pl_wid / wh_ratio, 1);
}

t_scene	*parse_main(int fd)
{
	int		res;
	char	*stroka;
	t_scene	*scene;

	scene = new_scene(0x0);
	while ((res = get_next_line(fd, &stroka)) > 0)
	{
		if ((res = parse_string(&scene, stroka)) < 0)
			return (NULL);
		free(stroka);
	}
	free(stroka);
	if (res < 0 || (res = parse_string(&scene, stroka)) < 0)
		return (NULL);
	set_cam(&scene);
	return (scene);
}
