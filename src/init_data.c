/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 03:07:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/19 22:12:21 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_data(t_data *data, t_img *img)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img = img;
	data->count = 1;
	data->coll_con = 0;
	data->y_column = 0;
	data->x_row = 0;
	data->map = NULL;
	data->player.i = 0;
	data->player.j = 0;
	data->exit.i = 0;
	data->exit.j = 0;
}

void	init_img(t_img *img)
{
	img->em_img = NULL;
	img->wall_img = NULL;
	img->col_img = NULL;
	img->exit_img = NULL;
	img->p_img = NULL;
}

void	fill_data(t_data *data, t_img *img, char *filename)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_ft_printf("mlx init failed.", data);
	fill_img(data, img);
	fill_map(data, filename);
}
