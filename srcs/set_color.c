/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:18:54 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 19:19:08 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_color_ambient(t_vector *color[4], float *bright, t_lstobj *lights)
{
	*bright += ((t_light *)lights->obj)->bright;
	color[1] = copy_vector(((t_light *)lights->obj)->color);
	color[0] = new_vector(color[2]->x + (color[1]->x + color[3]->x) *
(*bright), color[2]->y + (color[1]->y + color[3]->y) * (*bright),
color[2]->z + (color[1]->z + color[3]->z) * (*bright));
	free(color[1]);
	free(color[2]);
	set_maxmin_color(color[0]);
}

void	set_color_special_lights(float *bright, t_params *params,
t_lstobj *objects, t_lstobj *lights)
{
	*bright += compute_special_lights(params, (t_light *)lights->obj, objects);
	params->color[1] = new_vector(((((t_light *)lights->obj)->color->x *
((*bright) / params->scene->sum_bright)) - params->color[3]->x),
((((t_light *)lights->obj)->color->y * ((*bright) /
params->scene->sum_bright)) - params->color[3]->y),
((((t_light *)lights->obj)->color->z * ((*bright) /
params->scene->sum_bright)) - params->color[3]->z));
	params->color[0] = new_vector(params->color[2]->x + (params->color[3]->x
	+ (params->color[1]->x)), params->color[2]->y + (params->color[3]->y +
(params->color[1]->y)), params->color[2]->z + (params->color[3]->z +
(params->color[1]->z)));
	free(params->color[1]);
	free(params->color[2]);
	set_maxmin_color(params->color[0]);
}
