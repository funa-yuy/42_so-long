/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/20 20:10:36 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	window_close(t_data *data)
{
	free_data(data);
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	init_data(&data, &img);
	init_img(&img);
	if (argc != 2)
		exit_ft_printf("Check number of arguments.", &data);
	fill_data(&data, &img, argv[1]);
	validate_map_format(&data, data.x_row, data.y_column);
	data.win = mlx_new_window(data.mlx, data.x_row * IMG_SIZE, \
		data.y_column * IMG_SIZE, "so_long");
	disply_img(&data, data.p);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, window_close, &data);
	mlx_key_hook(data.win, key_push, &data);
	mlx_loop(data.mlx);
}
