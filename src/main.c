/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/13 17:55:21 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	// free(data->img);
	exit(0);
	return (0);
}

void	disply_img(t_data *data, void *p_img[1000][1000])
{
	int		x;
	int		y;

	y = 0;
	while (y < data->y_column)
	{
		x = 0;
		while (x < data->x_row)
		{
			mlx_put_image_to_window(data->mlx, data->win, \
				p_img[y][x], IMG_SIZE * x, IMG_SIZE * y);
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data, t_img *img)
{
	img->em_img = NULL;
	img->wall_img = NULL;
	img->col_img = NULL;
	img->exit_img = NULL;
	img->p_img = NULL;

	data->mlx = NULL;
	data->win = NULL;
	data->img = img;
	data->fd = -1;
	data->count = 1;
	data->coll_con = 0;
	data->y_column = 0;
	data->x_row = 0;
	data->player.x = 0;
	data->player.y = 0;
}


int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	if (argc != 2)
	{
		// ft_error_general("Check number of arguments.");
		ft_printf("Check number of arguments.\n");
		exit(1);
	}
	init_data(&data, &img);
	data.mlx = mlx_init();
//画像の読み込み
	read_img(&data, &img);
//MAPの読み込み
	read_map(&data, &img, argv[1]);
	if (map_error_cheack(&data, data.x_row, data.y_column, &img) == -1)
	{
		// ft_error_general("Check number of arguments.");
		exit(1);
	}
//ウィンドウ表示
	data.win = mlx_new_window(data.mlx, data.x_row * IMG_SIZE, \
		data.y_column * IMG_SIZE, "so_long");
//MAPの表示
	disply_img(&data, data.p);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, window_close, &data);
	mlx_key_hook(data.win, key_push, &data);
	mlx_loop(data.mlx);
}
