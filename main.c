/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/08 19:30:23 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "./lib/get_next_line/get_next_line.h"

# define T_SIZE 32

typedef struct s_img{
	char	**repo;
	char	**fill;
	int		y_column;//列(縦軸)
	int		x_row;//行(横軸)
	int		empty;//何もないとこの数
	int		wall;//数
	int		collects;//数
	int		exit;//数
	int		player;//数
	void	*em_img;
	void	*wall_img;
	void	*col_img;
	void	*exit_img;
	void	*p_img;
}				t_img;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	t_img	*img;
	int		fd;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	my_close(t_data *data)
{
	// printf("my_close keycode: %x\n", keycode);
	// printf("my_close data: %p\n", data);
	// printf("my_close img: %p\n", data->img);
	mlx_destroy_window(data->mlx, data->win);
	// free(data->img);
	exit(1);
	return (0);
}
int	my_key_close(int keycode, t_data *data)
{
	printf("my_key_close keycode: %x\n", keycode);
	if (keycode == XK_Escape)
		my_close(data);
	else if (keycode == XK_w)
		mlx_put_image_to_window(data->mlx, data->win, data->img->em_img, 50, 50);
	else if (keycode == XK_a)
		mlx_put_image_to_window(data->mlx, data->win, data->img->wall_img, 100, 100);
	else if (keycode == XK_s)
		mlx_put_image_to_window(data->mlx, data->win, data->img->col_img, 150, 150);
	else if (keycode == XK_d)
		mlx_put_image_to_window(data->mlx, data->win, data->img->exit_img, 200, 200);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->img->p_img, 10, 10);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void	my_mlx_put_map(t_data *data)
// {
// 	int	y;
// 	int	x;

// 	x = 0;
// 	while (x < 18)
// 	{
// 		y = 0;
// 		while (y < 10)
// 		{
// 			mlx_put_image_to_window(data->mlx, data->win, data->img,  T_SIZE * x, T_SIZE * y);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	*my_mlx_xpm_file_to_image(void *mlx, char *filename)
{
	int		fd;
	int		size;
	void	*img;

	size = T_SIZE;
	fd = open(filename, O_RDONLY);
	// if (fd < 0)
	// {
	// 	ft_fd_printf(2, "Error\nNo exist %s file\n", filename);
	// 	exit(1);
	// }
	close(fd);
	img = mlx_xpm_file_to_image(mlx, filename, &size, &size);
	// if (!img)
	// {
	// 	ft_fd_printf(2, "Error\nFailed create %s\n", filename);
	// 	exit(1);
	// }
	return (img);
}

void	read_img(t_data *data, t_img *img)
{
	img->em_img = my_mlx_xpm_file_to_image(data->mlx, "textures/empty.xpm");
	img->wall_img = my_mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm");
	img->col_img = my_mlx_xpm_file_to_image(data->mlx, "textures/collects.xpm");
	img->exit_img = my_mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm");
	img->p_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_10.xpm");
}


void	img_disply(t_data *data, int *components, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, T_SIZE * x, T_SIZE * y);
	(*components)++;
}

void	read_map(t_data *data, char *filename)
{
	char	*line;
	int	i;
	int	j;

	j = 0;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		printf("Error\nNo such file or directory\n");
	line = get_next_line(data->fd);
	if (line == NULL)
		printf("Map file is empty.");

	while (line != NULL && line[0] != '\n')
	{
		i = 0;
		while(line[i] != '\0')
		{
			if (line[i] == '0')
				img_disply(data, &data->img->empty, data->img->em_img, i, j);
			else if (line[i] == '1')
				img_disply(data, &data->img->wall, data->img->wall_img, i, j);
			else if (line[i] == 'C')
				img_disply(data, &data->img->collects, data->img->col_img, i, j);
			else if (line[i] == 'E')
				img_disply(data, &data->img->exit, data->img->exit_img, i, j);
			else if (line[i] == 'P')
				img_disply(data, &data->img->player, data->img->p_img, i, j);
			i++;
		}
		data->img->x_row = --i;
		free(line);
		line = get_next_line(data->fd);
		j++;
	}
	data->img->y_column = j;
	free(line);
	close(data->fd);
}

int	main(int argc, char **argv)
{
	(void)argc;
	// void	*mlx;
	t_data	data;
	t_img	img = {0};
	// void	*mlx_win;

	data.mlx = mlx_init();
	// data.img = mlx_new_image(data.mlx, 500, 500);

//画像の読み込み
	data.img = &img;
	read_img(&data, &img);
	// read_map(&data, argv[1]);
	// data.win = mlx_new_window(data.mlx, data.img->y_column * T_SIZE, data.img->x_row * T_SIZE, "Hello world!");
	data.win = mlx_new_window(data.mlx, 416, 160, "Hello world!");
//MAPの読み込み
	read_map(&data, argv[1]);
	// my_mlx_put_map(&data);

	// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
	// 							&data.endian);
	// data.addr[0] = 0x33; // Blue
	// data.addr[1] = 0xCC; // Green
	// data.addr[2] = 0xFF; // Red
	// data.addr[3] = 0xFF;
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, my_close, &data);
	mlx_key_hook(data.win, my_key_close, &data);
	mlx_loop(data.mlx);
}
