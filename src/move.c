/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:49:25 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 16:23:03 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	can_move(t_data *data, t_img *img, void *p_next)
{
	if (p_next == img->wall_img || \
		(p_next == img->exit_img && data->coll_con != 0))
		return (false);
	if (p_next == img->exit_img && data->coll_con == 0)
	{
		ft_printf("Game Clear!!!\n");
		window_close(data);
	}
	return (true);
}

void	move_player_x(t_data *data, int x, int y, int m)
{
	int		next_x;
	int		now_y;
	t_img	*img;

	img = data->img;
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	if (can_move(data, img, data->p[y][x + m]) == false)
		return ;
	if (data->p[y][x + m] == img->col_img)
	{
		data->coll_con--;
		ft_printf("get collect %d\n", data->coll_con);
	}
	data->p[y][x + m] = img->p_img;
	data->p[y][x] = img->em_img;
	next_x = IMG_SIZE * x + (IMG_SIZE * m);
	now_y = IMG_SIZE * y;
	mlx_put_image_to_window(data->mlx, data->win, \
							data->p[y][x + m], next_x, now_y);
	mlx_put_image_to_window(data->mlx, data->win, \
							data->p[y][x], IMG_SIZE * x, now_y);
	data->player.x = x + m;
}

void	move_player_y(t_data *data, int x, int y, int m)
{
	int		now_x;
	int		next_y;
	t_img	*img;

	img = data->img;
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	if (can_move(data, img, data->p[y + m][x]) == false)
		return ;
	if (data->p[y + m][x] == img->col_img)
	{
		data->coll_con--;
		ft_printf("get collect %d\n", data->coll_con);
	}
	data->p[y + m][x] = img->p_img;
	data->p[y][x] = img->em_img;
	now_x = IMG_SIZE * x;
	next_y = IMG_SIZE * y + (IMG_SIZE * m);
	mlx_put_image_to_window(data->mlx, data->win, \
							data->p[y + m][x], now_x, next_y);
	mlx_put_image_to_window(data->mlx, data->win, \
							data->p[y][x], now_x, IMG_SIZE * y);
	data->player.y = y + m;
}

int	key_push(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		window_close(data);
	else if (keycode == XK_w || keycode == XK_Up)
		move_player_y(data, data->player.x, data->player.y, -1);
	else if (keycode == XK_a || keycode == XK_Left)
		move_player_x(data, data->player.x, data->player.y, -1);
	else if (keycode == XK_s || keycode == XK_Down)
		move_player_y(data, data->player.x, data->player.y, 1);
	else if (keycode == XK_d || keycode == XK_Right)
		move_player_x(data, data->player.x, data->player.y, 1);
	return (0);
}
