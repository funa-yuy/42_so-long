/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:59:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/08 02:19:44 by miyuu            ###   ########.fr       */
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
	int		y_column;//列(縦軸)
	int		x_row;//行(横軸)
	int		empty;//敵の数
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


// void	img_disply(int components, void	*img, int x, int y)
// {
// 	// mlx_put_image_to_window(data->mlx, data->win, img, T_SIZE * x, T_SIZE * y);
// 	components++;
// }

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
				printf("0");
			else if (line[i] == '1')
				printf("1");
			else if (line[i] == 'C')
				printf("C");
			else if (line[i] == 'E')
				printf("E");
			else if (line[i] == 'P')
				printf("P");
			i++;
		}
		printf("\n");
		data->img->x_row = i;
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
	t_img	img;
	// void	*mlx_win;

//画像の読み込み
	data.img = &img;
	// read_img(&data, &img);
//MAPの読み込み
	read_map(&data, argv[1]);
	// my_mlx_put_map(&data);
	return (0);
}
