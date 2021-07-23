/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:33:11 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/23 15:33:14 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_pixel_put(t_mlx *mmlx, int x, int y, int color)
{
	char *addr;

	addr = mmlx->addr + (y * mmlx->line_length + x * mmlx->bpp / 8);
	*(unsigned int *)addr = color;
}

void	fill_image(t_mlx *mmlx, int x, int y)
{
	t_vector	*d;
	int			c;
	t_vector	*temp;

	d = new_vector(x * mmlx->scene->vplane->width /
mmlx->scene->vport->width, y * mmlx->scene->vplane->height /
mmlx->scene->vport->height, 1);
	temp = d;
	d = make_cam_crd(d, ((t_camera *)mmlx->scene->cams->obj)->direction);
	free(temp);
	normalise_vect(d);
	c = raytraycing(*d, mmlx->scene);
	my_pixel_put(mmlx, x + (mmlx->scene->vport->width / 2),
-y + (mmlx->scene->vport->height / 2), c);
	free(d);
}

void	create_image(t_mlx *mmlx)
{
	t_vector	*cam_crd;
	int			x;
	int			y;

	if (!(t_camera *)mmlx->scene->cams)
		print_errors(-2);
	cam_crd = ((t_camera *)mmlx->scene->cams->obj)->coords;
	y = (mmlx->scene->vport->height / 2);
	while (y > -mmlx->scene->vport->height / 2)
	{
		x = -(mmlx->scene->vport->width / 2);
		while (x < mmlx->scene->vport->width / 2)
		{
			fill_image(mmlx, x, y);
			((t_camera *)mmlx->scene->cams->obj)->coords = cam_crd;
			mmlx->scene->depth = 3;
			x++;
		}
		y--;
	}
}
