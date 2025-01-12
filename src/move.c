/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:49:25 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/12 18:18:24 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


void	move_player_x(t_data *data, t_img *img, int x, int y, int m)
{
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	//壁だったとき
	if (data->p[y][x + m] == img->wall_img || (data->p[y][x + m] == img->exit_img && data->coll_con != 0))
		return;
	//出口だったとき
	if (data->p[y][x + m] == img->exit_img && data->coll_con == 0)
	{
		ft_printf("Game Clear\n");
		window_close(data);
	}
	if (data->p[y][x + m] == img->col_img)
	{
		data->coll_con--;
		ft_printf("Get 貝\n");
	}
	data->p[y][x + m] = img->p_img;
	data->p[y][x] = img->em_img;
	mlx_put_image_to_window(data->mlx, data->win, data->p[y][x + m], IMG_SIZE * x + (IMG_SIZE * m), IMG_SIZE * y);
	mlx_put_image_to_window(data->mlx, data->win, data->p[y][x], IMG_SIZE * x, IMG_SIZE * y);

	data->player.x = x + m;
}

void	move_player_y(t_data *data, t_img *img, int x, int y, int m)
{
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	//壁だったとき
	if (data->p[y + m][x] == img->wall_img || (data->p[y + m][x] == img->exit_img && data->coll_con != 0))
		return;
	//出口だったとき
	if (data->p[y + m][x] == img->exit_img && data->coll_con == 0)
	{
		ft_printf("Game Clear\n");
		window_close(data);
	}
	if (data->p[y + m][x] == img->col_img)
	{
		data->coll_con--;
		ft_printf("Get 貝\n");
	}
	data->p[y + m][x] = img->p_img;
	data->p[y][x] = img->em_img;
	mlx_put_image_to_window(data->mlx, data->win, data->p[y + m][x], IMG_SIZE * x, IMG_SIZE * y + (IMG_SIZE * m));
	mlx_put_image_to_window(data->mlx, data->win, data->p[y][x], IMG_SIZE * x, IMG_SIZE * y);

	data->player.y = y + m;
}

int	key_push(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		window_close(data);
	else if (keycode == XK_w || keycode == XK_Up)
	{
		move_player_y(data, data->img, data->player.x, data->player.y, -1);
		ft_printf("key push w\n");
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		move_player_x(data, data->img, data->player.x, data->player.y, -1);
		ft_printf("key push a\n");
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		move_player_y(data, data->img, data->player.x, data->player.y, 1);
		ft_printf("key push s\n");
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		move_player_x(data, data->img, data->player.x, data->player.y, 1);
		ft_printf("key push d\n");
	}
	return (0);
}
