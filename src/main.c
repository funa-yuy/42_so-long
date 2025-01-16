/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/17 04:44:32 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	disply_img(t_data *data, void *p_img[MAX_MAP][MAX_MAP])
{
	int		x;
	int		y;

	y = 0;
	while (y < data->y_column)
	{
		x = 0;
		while (x < data->x_row)
		{
			mlx_put_image_to_window(data->mlx, data->win, p_img[y][x], \
				IMG_SIZE * x, IMG_SIZE * y);
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
	data->count = 1;
	data->coll_con = 0;
	data->y_column = 0;
	data->x_row = 0;
	data->player.x = 0;
	data->player.y = 0;
}

int	error_ft_printf(char *msg)
{
	ft_printf("%s\n", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	if (argc != 2)
		error_ft_printf("Check number of arguments.");
	init_data(&data, &img);
	data.mlx = mlx_init();
//画像の読み込み
	read_img(&data, &img);
//MAPの読み込み
	read_map(&data, &img, argv[1]);
	map_error_cheack(&data, data.x_row, data.y_column, &img);
//ウィンドウ表示
	data.win = mlx_new_window(data.mlx, data.x_row * IMG_SIZE, \
		data.y_column * IMG_SIZE, "so_long");
//MAPの表示
	disply_img(&data, data.p);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, window_close, &data);
	mlx_key_hook(data.win, key_push, &data);
	mlx_loop(data.mlx);
}
