/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 03:22:21 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/24 03:22:24 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_pic(char **pic, t_mlx *mmlx)
{
	int x;
	int y;
	int i;
	int j;

	y = mmlx->scene->vport->height - 1;
	i = 122;
	while (y)
	{
		x = 0;
		while (x < mmlx->scene->vport->width)
		{
			j = x * mmlx->bpp / 8 + y * mmlx->line_length;
			*(*pic + i++) = *(mmlx->addr + j++);
			*(*pic + i++) = *(mmlx->addr + j++);
			*(*pic + i++) = *(mmlx->addr + j);
			x++;
		}
		y--;
	}
}

void	fill_header(char **pic, t_mlx *mmlx)
{
	unsigned int size;

	size = mmlx->scene->vport->width * mmlx->scene->vport->height * 3;
	*(unsigned short *)*pic = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*pic + 2) = size + 122;
	*(unsigned int *)(*pic + 6) = 0u;
	*(unsigned char *)(*pic + 10) = 122;
	*(unsigned int *)(*pic + 14) = 122 - 14;
	*(unsigned int *)(*pic + 18) = mmlx->scene->vport->width;
	*(unsigned int *)(*pic + 22) = mmlx->scene->vport->height;
	*(unsigned short *)(*pic + 26) = 1;
	*(unsigned short *)(*pic + 28) = 24;
	*(unsigned int *)(*pic + 30) = 0;
	*(unsigned int *)(*pic + 34) = (unsigned int)size;
	*(unsigned int *)(*pic + 38) = 3780;
	*(unsigned int *)(*pic + 42) = 3780;
	*(int *)(*pic + 46) = 0;
	*(int *)(*pic + 50) = 0;
}

void	make_bmp(t_mlx *mmlx)
{
	unsigned int	size;
	char			*pic;
	int				fd;
	unsigned int	i;

	size = mmlx->scene->vport->width * mmlx->scene->vport->height * 3 + 122;
	if (!(pic = malloc(size)))
		print_errors(-6);
	i = 0;
	while (i < size)
		pic[i++] = 0;
	fill_header(&pic, mmlx);
	fill_pic(&pic, mmlx);
	if ((fd = open("my_bmp.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		print_errors(-7);
	write(fd, pic, size);
	close(fd);
}
