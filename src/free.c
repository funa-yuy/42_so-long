/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:53:46 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/19 22:11:55 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_data(t_data *data)
{
	free_map(data, data->y_column);
	if (data->img)
		free_img(data, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

// NOTE: 最小限のデータだけ渡すのが本来良さそうだよね
void	free_map(t_data *data, int rows)
{
	int	i;

	if (data->map == NULL)
		return ;
	i = 0;
	while (i < rows)
	{
		if (data->map[i])
			free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void	free_img(t_data *data, t_img *img)
{
	if (img->em_img)
		mlx_destroy_image(data->mlx, img->em_img);
	if (img->wall_img)
		mlx_destroy_image(data->mlx, img->wall_img);
	if (img->col_img)
		mlx_destroy_image(data->mlx, img->col_img);
	if (img->exit_img)
		mlx_destroy_image(data->mlx, img->exit_img);
	if (img->p_img)
		mlx_destroy_image(data->mlx, img->p_img);
}
