/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 04:39:28 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/18 16:50:45 by mfunakos         ###   ########.fr       */
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

bool	is_surrounded_walls(t_data *data, t_img *img, int width, int height)
{
	int		i;

	i = 0;
	while (i < width)
	{
		if (data->p[0][i] != img->wall_img || data->p[height - 1][i] != img->wall_img)
			return (false);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (data->p[i][0] != img->wall_img || data->p[i][width - 1] != img->wall_img)
			return (false);
		i++;
	}
	return (true);
}

void	validate_map(t_data *data, int width, int height)
{
	if (data->player.i == 0 && data->player.j == 0)
		exit_ft_printf("[MAP ERROR]The 'P' element is incorrect.", data);
	if (data->exit.i == 0 && data->exit.j == 0)
		exit_ft_printf("[MAP ERROR]The 'E' element is incorrect.", data);
	if (data->coll_con == 0)
		exit_ft_printf("[MAP ERROR]The 'C' element is incorrect.", data);
	if (!(is_surrounded_walls(data, data->img, width, height)))
		exit_ft_printf("[MAP ERROR]The map is not surrounded by walls.", data);
	if (can_goal(data, data->map, data->x_row, data->y_column))
		free_map(data->map, data->y_column);
	else
	{
		free_map(data->map, data->y_column);
		exit_ft_printf("[MAP ERROR] Impossible to reach goal.", data);
	}
}
