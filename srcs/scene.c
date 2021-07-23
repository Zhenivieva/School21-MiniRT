/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:30:01 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:30:04 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*new_scene(int color)
{
	t_scene	*scene;

	if (!(scene = malloc(sizeof(t_scene))))
		print_errors(-6);
	scene->vport = NULL;
	scene->vplane = NULL;
	scene->cams = NULL;
	scene->objs = NULL;
	scene->lights = NULL;
	scene->background_color = color;
	scene->depth = 2;
	scene->sum_bright = 0;
	scene->t_min = 0.001;
	scene->t_max = -1;
	return (scene);
}
