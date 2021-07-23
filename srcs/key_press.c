/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 21:57:26 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 21:57:29 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_press(int b, t_mlx *mmlx)
{
	t_vector *coord;
	t_vector *dir;

	if (b == 53)
		return (finish());
	if (b == 35)
		mmlx->scene->cams = (t_lstobj *)mmlx->scene->cams->prev;
	if (b == 45)
		mmlx->scene->cams = (t_lstobj *)mmlx->scene->cams->next;
	coord = ((t_camera *)mmlx->scene->cams->obj)->coords;
	dir = ((t_camera *)mmlx->scene->cams->obj)->direction;
	coord->x += ((b == 86) ? -1 : 0) + ((b == 88) ? 1 : 0);
	coord->y += ((b == 84) ? -1 : 0) + ((b == 91) ? 1 : 0);
	coord->z += ((b == 78) ? -1 : 0) + ((b == 69) ? 1 : 0);
	dir->x += ((b == 123) ? 0.5 : 0) + ((b == 124) ? -0.5 : 0);
	dir->y += ((b == 125) ? 0.2 : 0) + ((b == 126) ? -0.2 : 0);
	create_image(mmlx);
	mlx_clear_window(mmlx->mlx, mmlx->win);
	mlx_put_image_to_window(mmlx->mlx, mmlx->win, mmlx->img, 0, 0);
	return (0);
}
