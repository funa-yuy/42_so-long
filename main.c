/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/05 16:55:15 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>

# define T_SIZE 64
# define ESC 53

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	void	*c_img;
	void	*e_img;
	void	*w_img;
	void	*b_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	my_key_close(int keycode, t_data *vars)
{
	if (keycode == XK_Escape)
		mlx_destroy_window(vars->mlx, vars->win);
	else if (keycode == XK_w)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->c_img, 50, 50);
	else if (keycode == XK_a)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->e_img, 100, 100);
	else if (keycode == XK_s)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->w_img, 150, 150);
	else if (keycode == XK_d)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->b_img, 200, 200);
	else
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 10, 10);
	return (0);
}

int	my_close(int keycode, t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	// free(vars->img);
	// exit(1);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

int	read_img(t_data *vars)
{
	vars->img = my_mlx_xpm_file_to_image(vars->mlx, "textures/p.xpm");
	vars->c_img = my_mlx_xpm_file_to_image(vars->mlx, "textures/c.xpm");
	vars->e_img = my_mlx_xpm_file_to_image(vars->mlx, "textures/e.xpm");
	vars->w_img = my_mlx_xpm_file_to_image(vars->mlx, "textures/1.xpm");
	vars->b_img = my_mlx_xpm_file_to_image(vars->mlx, "textures/0.xpm");
	return (0);
}

int	main(void)
{
	void	*mlx;
	t_data	vars;
	void	*mlx_win;

	vars.mlx = mlx_init();
	// vars.img = mlx_new_image(vars.mlx, 500, 500);
	read_img(&vars);
	vars.win = mlx_new_window(vars.mlx, 600, 500, "Hello world!");
	// vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length,
	// 							&vars.endian);
	// vars.addr[0] = 0x33; // Blue
	// vars.addr[1] = 0xCC; // Green
	// vars.addr[2] = 0xFF; // Red
	// vars.addr[3] = 0xFF;
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_hook(vars.win, 17, 1L<<2, my_close, &vars);
	mlx_hook(vars.win, 2, 1L<<0, my_key_close, &vars);
	mlx_loop(vars.mlx);
}
