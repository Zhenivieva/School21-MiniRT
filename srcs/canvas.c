/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:27:16 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:27:19 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_canvas	*new_canvas(float width, float height, float distance)
{
	t_canvas *canvas;

	if (!(canvas = malloc(sizeof(t_camera))))
		print_errors(-6);
	canvas->height = height;
	canvas->width = width;
	canvas->distance = distance;
	return (canvas);
}
