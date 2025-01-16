/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:49:25 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 05:25:12 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	can_move(t_data *data, t_img *img, void *p_next[][])
{
	if (p_next == img->wall_img || \
		(p_next == img->exit_img && data->coll_con != 0))
		return (false);
	if (p_next == img->exit_img && data->coll_con == 0)
	{
		ft_printf("Game Clear\n");
		window_close(data);
	}
	retuen (true);
}

void	move_player_x(t_data *data, int x, int y, int m)
{
	void	*p_cur[][];
	void	*p_next[][];
	int		next_x;
	int		next_y;
	t_img	*img;

	img = data->img;
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	p_cur = data->p[y][x];
	p_next = data->p[y][x + m];
	if (can_move(data, img, p_next) == false)
		return ;
	if (p_next == img->col_img)
		data->coll_con--;
	p_next = img->p_img;
	p_cur = img->em_img;
	next_x = IMG_SIZE * x + (IMG_SIZE * m);
	now_y = IMG_SIZE * y;
	mlx_put_image_to_window(data->mlx, data->win, p_next, next_x, now_y);
	mlx_put_image_to_window(data->mlx, data->win, p_cur, IMG_SIZE * x, now_y);
	data->player.x = x + m;
}

void	move_player_y(t_data *data, int x, int y, int m)
{
	void	*p_cur[][];
	void	*p_next[][];
	int		next_x;
	int		next_y;
	t_img	*img;

	img = data->img;
	ft_printf("Moves => %d times\n", data->count);
	data->count++;
	p_cur = data->p[y][x];
	p_next = data->p[y + m][x];
	if (can_move(data, img, p_next) == false)
		return ;
	if (p_next == img->col_img)
		data->coll_con--;
	p_next = img->p_img;
	p_cur = img->em_img;
	now_x = IMG_SIZE * x;
	next_y = IMG_SIZE * y + (IMG_SIZE * m);
	mlx_put_image_to_window(data->mlx, data->win, p_next, next_x, next_y);
	mlx_put_image_to_window(data->mlx, data->win, p_cur, next_x, IMG_SIZE * y);
	data->player.y = y + m;
}

int	key_push(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		window_close(data);
	else if (keycode == XK_w || keycode == XK_Up)
	{
		move_player_y(data, data->player.x, data->player.y, -1);
		ft_printf("key push w\n");
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		move_player_x(data, data->player.x, data->player.y, -1);
		ft_printf("key push a\n");
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		move_player_y(data, data->player.x, data->player.y, 1);
		ft_printf("key push s\n");
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		move_player_x(data, data->player.x, data->player.y, 1);
		ft_printf("key push d\n");
	}
	return (0);
}
