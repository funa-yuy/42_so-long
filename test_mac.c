/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:59:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/08 18:06:29 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include <X11/keysym.h>
// #include <X11/X.h>

#include "./lib/get_next_line/get_next_line.h"


# define T_SIZE 32

typedef struct s_img{
	char	**repo;
	char	**fill;
	int	y_column;//列(縦軸)
	int	x_row;//行(横軸)
	int	empty;//敵の数
	int	wall;//数
	int	collects;//数
	int	exit;//数
	int	player;//数
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


// void	*my_mlx_xpm_file_to_image(void *mlx, char *filename)
// {
// 	int		fd;
// 	int		size;
// 	void	*img;

// 	size = T_SIZE;
// 	fd = open(filename, O_RDONLY);
// 	// if (fd < 0)
// 	// {
// 	// 	ft_fd_printf(2, "Error\nNo exist %s file\n", filename);
// 	// 	exit(1);
// 	// }
// 	close(fd);
// 	img = mlx_xpm_file_to_image(mlx, filename, &size, &size);
// 	// if (!img)
// 	// {
// 	// 	ft_fd_printf(2, "Error\nFailed create %s\n", filename);
// 	// 	exit(1);
// 	// }
// 	return (img);
// }

// void	read_img(t_data *data, t_img *img)
// {
// 	img->em_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_00.xpm");
// 	img->wall_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_05.xpm");
// 	img->col_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_10.xpm");
// 	img->exit_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_15.xpm");
// 	img->p_img = my_mlx_xpm_file_to_image(data->mlx, "textures/souzou/souzou_got_19.xpm");
// }


void	img_disply(int *components, void	*img, int x, int y, char s)
{
	(void)img;
	// mlx_put_image_to_window(data->mlx, data->win, img, T_SIZE * x, T_SIZE * y);
	(*components)++;
	printf("%c 合計:%d x:%d y:%d \n", s, *components, T_SIZE * x, T_SIZE * y);
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
		printf("player : %d\n", data->img->player);
		i = 0;
		while(line[i] != '\0')
		{
			if (line[i] == '0')
				img_disply(&data->img->empty, data->img->em_img, j, i, line[i]);
			else if (line[i] == '1')
				img_disply(&data->img->wall, data->img->wall_img, j, i, line[i]);
			else if (line[i] == 'C')
				img_disply(&data->img->collects, data->img->col_img, j, i, line[i]);
			else if (line[i] == 'E')
				img_disply(&data->img->exit, data->img->exit_img, j, i, line[i]);
			else if (line[i] == 'P')
				img_disply(&data->img->player, data->img->p_img, j, i, line[i]);
			i++;
		}
		printf("\n");
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
	t_img   img = {0};  // 全てのメンバを0で初期化
	// void	*mlx_win;

//画像の読み込み
	data.img = &img;
	// read_img(&data, &img);
//MAPの読み込み
	read_map(&data, argv[1]);
	printf("empty = %d\n", data.img->empty);
	printf("wall = %d\n", data.img->wall);
	printf("collects = %d\n", data.img->collects);
	printf("exit = %d\n", data.img->exit);
	printf("player = %d\n", data.img->player);
	printf("y_column = %d\n", data.img->y_column);
	printf("x_row = %d\n", data.img->x_row);
	// my_mlx_put_map(&data);
	return (0);
}
