

#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "./lib/get_next_line/get_next_line.h"



// void	img_disply(t_data *data, int *components, void *img, int x, int y)
// {
// 	mlx_put_image_to_window(data->mlx, data->win, img, T_SIZE * x, T_SIZE * y);
// 	(*components)++;
// }

void	move_player_x(t_data *data, void *img, int x, int y, int m)
{
	//壁だったとき
	if (p[player->y][player->x + m]->game_img == img->wall_img)
		return;

	data->p[y][x + m]->game_img = img->p_img;
	data->p[y][x]->game_img = img->em_img;
	mlx_put_image_to_window(data->mlx, data->win, data->p[y][x + m]->game_img, T_SIZE * x + (T_SIZE * m), T_SIZE * y);
	mlx_put_image_to_window(data->mlx, data->win, data->p[y][x]->game_img, T_SIZE * x, T_SIZE * y);

	//出口だったとき
	if (p[player->y][player->x + m]->game_img == img->exit_img)
	{
		printf("Game Clear\n");
		my_close(data);
	}
	data->player->x = x + m;
}


int	my_key_push(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		my_close(data);
	else if (keycode == XK_w || keycode == XK_Up)
	{
		move_player_x(&data, data->img, data->player->x, data->player->y, 1);
		printf("key push w\n");
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		move_player_y(&data, data->img, data->player->x, data->player->y, 1);
		printf("key push a\n");
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		move_player_x(&data, data->img, data->player->x, data->player->y, -1);
		printf("key push s\n");
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		move_player_y(&data, data->img, data->player->x, data->player->y, -1);
		printf("key push d\n");
	}
	return (0);
}


void	img_disply(t_data *data, int *components, void *img, int x, int y)
{

	while (y <= data->img->y_column )
	{
		while (x <= data->img->x_row)
		{
			mlx_put_image_to_window(data->mlx, data->win, p[y][x]->img, T_SIZE * x, T_SIZE * y);
			x++;
		}
		y++;
	}
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
				data->p[j][i] = (t_point){i, j, img->em_img};
			else if (line[i] == '1')
				data->p[j][i] = (t_point){i, j, img->wall_img};
			else if (line[i] == 'C')
				data->p[j][i] = (t_point){i, j, img->col_img};
			else if (line[i] == 'E')
				data->p[j][i] = (t_point){i, j, img->exit_img};
			else if (line[i] == 'P')
			{
				data->p[j][i] = (t_point){i, j, img->p_img};
				data->player = (t_point){i, j, img->p_img};
			}
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
	t_data	data;
	t_img	img = {0};

	data.mlx = mlx_init();

//画像の読み込み
	data.img = &img;
	read_img(&data, &img);
//MAPの読み込み
	read_map(&data, argv[1]);
//ウィンドウ表示
	data.win = mlx_new_window(data.mlx, data.y_column * T_SIZE, data.x_row * T_SIZE, "so_long");

	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, my_close, &data);
	mlx_key_hook(data.win, my_key_push, &data);
	mlx_loop(data.mlx);
}
