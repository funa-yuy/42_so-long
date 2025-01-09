/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_linux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 19:45:41 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/09 20:16:23 by mfunakos         ###   ########.fr       */
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

typedef struct s_player{
	int			x;
	int			y;
}			t_player;

typedef struct s_img{
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
	int		y_column;//列(縦軸)
	int		x_row;//行(横軸)
	void	*p[1000][1000];
	t_player player;
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
	if (keycode == XK_Escape)
		my_close(data);
	else if (keycode == XK_w || keycode == XK_Up)
			printf("key push w\n");
	else if (keycode == XK_a || keycode == XK_Left)
			printf("key push a\n");
	else if (keycode == XK_s || keycode == XK_Down)
			printf("key push s\n");
	else if (keycode == XK_d || keycode == XK_Right)
			printf("key push d\n");
	return (0);
}

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
	img->p_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_01.xpm");
}


void	img_disply(t_data *data, void *p_img[1000][1000])
{
	int		x;
	int		y;

	y = 0;
	while (y < data->y_column)
	{
		x = 0;
		while (x < data->x_row)
		{
			mlx_put_image_to_window(data->mlx, data->win, p_img[y][x], T_SIZE * x, T_SIZE * y);
			x++;
		}
		y++;
	}
}

void	read_map(t_data *data, t_img *img, char *filename)
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
				data->p[j][i] = img->em_img;
			else if (line[i] == '1')
				data->p[j][i] = img->wall_img;
			else if (line[i] == 'C')
				data->p[j][i] = img->col_img;
			else if (line[i] == 'E')
				data->p[j][i] = img->exit_img;
			else if (line[i] == 'P')
			{
				data->p[j][i] = img->p_img;
				data->player = (t_player){i, j};
			}
			i++;
		}
		data->x_row = --i;
		free(line);
		line = get_next_line(data->fd);
		j++;
	}
	data->y_column = j;
	free(line);
	close(data->fd);
}

int	main(int argc, char **argv)
{
	(void)argc;
	t_data	data;
	t_img	img = {0};

	data.mlx = mlx_init();

//画像の読み込み
	data.img = &img;
	read_img(&data, &img);
//MAPの読み込み
	read_map(&data, &img, argv[1]);
//ウィンドウ表示
	data.win = mlx_new_window(data.mlx, data.x_row * T_SIZE, data.y_column * T_SIZE, "so_long");

//MAPの表示
	img_disply(&data, data.p);


	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, my_close, &data);
	mlx_key_hook(data.win, my_key_close, &data);
	mlx_loop(data.mlx);
}
