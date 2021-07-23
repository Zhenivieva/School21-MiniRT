/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:27:52 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:27:55 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*new_light(int type, t_vector *coords, float bright, t_vector *color)
{
	t_light *light;

	if (!(light = malloc(sizeof(t_light))))
		print_errors(-6);
	light->type = type;
	light->coords = coords;
	light->bright = bright;
	light->color = color;
	return (light);
}
