/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 04:39:28 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/18 05:00:06 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

bool	is_surrounded_walls(void **p, t_img *img, int width, int height)
{
	int		i;

	i = 0;
	while (i < width)
	{
		if (p[0][i] != img->wall_img || p[height - 1][i] != img->wall_img)
			return (false);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (p[i][0] != img->wall_img || p[i][width - 1] != img->wall_img)
			return (false);
		i++;
	}
	return (true);
}

void	validate_map(t_data *data, int width, int height)
{
	int	s_x;
	int	s_y;

	s_x = data->player.i;
	s_y = data->player.j;
	if (s_x == 0 || s_y == 0 || s_x == width - 1 || s_y == height - 1)
		exit_ft_printf("[MAP ERROR]The 'P' element is incorrect.", data);
	if (!(is_surrounded_walls(data->p, data->img, width, height)))
		exit_ft_printf("[MAP ERROR]The map is not surrounded by walls.", data);
	if (can_goal(data, data->map, data->x_row, data->y_column))
		free_map(data->map, data->y_column);
	else
	{
		free_map(data->map, data->y_column);
		exit_ft_printf("[MAP ERROR] Impossible to reach goal.", data);
	}
}
