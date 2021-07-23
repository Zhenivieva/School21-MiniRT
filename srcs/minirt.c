/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:55:22 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/06 17:55:29 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		finish(void)
{
	exit(0);
	return (0);
}

t_mlx	*create_mmlx(t_scene *scene, int argc)
{
	t_mlx	*mmlx;
	int		w;
	int		h;

	if (!(mmlx = malloc(sizeof(t_mlx))))
		print_errors(-6);
	mmlx->mlx = mlx_init();
	if (!(mmlx->mlx = mlx_init()))
		print_errors(-8);
	mmlx->scene = scene;
	mlx_get_screen_size(mmlx->mlx, &w, &h);
	(mmlx->scene->vport->width > w && argc != 3) ? mmlx->scene->vport->
width = w : 0;
	(mmlx->scene->vport->height > h && argc != 3) ? mmlx->scene->vport->
height = h : 0;
	mmlx->img = mlx_new_image(mmlx->mlx, mmlx->scene->vport->width,
mmlx->scene->vport->height);
	mmlx->addr = mlx_get_data_addr(mmlx->img, &mmlx->bpp,
&mmlx->line_length, &mmlx->endian);
	mmlx->win = mlx_new_window(mmlx->mlx, mmlx->scene->vport->width,
mmlx->scene->vport->height, "MyWindow");
	return (mmlx);
}

void	open_scene_file(int *fd, char *sc_file)
{
	if ((*fd = open(sc_file, O_RDONLY)) <= 0)
		print_errors(-4);
	while ((*sc_file) && (*sc_file != '.'))
		sc_file++;
	if (!(*sc_file) || (ft_strncmp(sc_file, ".rt", 3)))
		print_errors(-5);
}

int		main(int argc, char **argv)
{
	t_mlx	*mmlx;
	t_scene	*scene;
	int		fd;

	if (argc < 2 || argc > 3)
		print_errors(-1);
	open_scene_file(&fd, argv[1]);
	if (!(scene = parse_main(fd)))
		print_errors(-2);
	close(fd);
	mmlx = create_mmlx(scene, argc);
	set_viewplane(&scene);
	create_image(mmlx);
	if (argc == 2)
	{
		mlx_clear_window(mmlx->mlx, mmlx->win);
		mlx_put_image_to_window(mmlx->mlx, mmlx->win, mmlx->img, 0, 0);
		mlx_hook(mmlx->win, 2, 1L << 0, key_press, mmlx);
		mlx_hook(mmlx->win, 17, 1L << 17, finish, mmlx);
		mlx_loop(mmlx->mlx);
	}
	if (argc == 3)
		((ft_strncmp(argv[2], "--save", 6))) ? print_errors(-3) :
make_bmp(mmlx);
	return (0);
}
