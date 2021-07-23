/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:27:00 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 14:51:30 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*new_camera(t_vector *coords, t_vector *direction, int fov)
{
	t_camera *camera;

	direction->x *= -1;
	direction->y *= -1;
	if (!(camera = malloc(sizeof(t_camera))))
		print_errors(-6);
	camera->coords = coords;
	camera->direction = direction;
	camera->fov = fov;
	return (camera);
}

void		set_cam(t_scene **scene)
{
	t_lstobj *cams;

	cams = (*scene)->cams;
	(*scene)->cam_num = 0;
	if (cams)
	{
		(*scene)->cam_num++;
		while (cams->next)
		{
			(*scene)->cam_num++;
			((t_lstobj *)cams->next)->prev = cams;
			cams = cams->next;
		}
		cams->next = (*scene)->cams;
		(*scene)->cams->prev = cams;
	}
}

t_vector	*make_cam_crd(t_vector *coord, t_vector *dir_cam)
{
	t_vector *cx;
	t_vector *cy;
	t_vector *cz;
	t_vector *temp;

	cz = dir_cam;
	cx = cross_vect((t_vector){0, 1, 0}, *dir_cam);
	cy = cross_vect(*dir_cam, *cx);
	temp = new_vector(coord->x * cx->x + coord->y * cx->y + coord->z * cx->z,
coord->x * cy->x + coord->y * cy->y + coord->z * cy->z,
coord->x * cz->x + coord->y * cz->y + coord->z * cz->z);
	free(cx);
	free(cy);
	return (temp);
}
