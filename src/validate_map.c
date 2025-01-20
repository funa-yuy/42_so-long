/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 04:39:28 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/20 23:05:19 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	is_surrounded_walls(t_data *data, t_img *img, int width, int height)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (data->p[0][i] != img->wall_img || \
			data->p[height - 1][i] != img->wall_img)
			return (false);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (data->p[i][0] != img->wall_img || \
			data->p[i][width - 1] != img->wall_img)
			return (false);
		i++;
	}
	return (true);
}

bool	is_only_one_p_e(t_data *data, t_img *img, int width, int height)
{
	int	con_player;
	int	con_exit;
	int	j;
	int	i;

	con_player = 0;
	con_exit = 0;
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			if (data->p[j][i] == img->p_img)
				con_player++;
			if (data->p[j][i] == img->exit_img)
				con_exit++;
			i++;
		}
		j++;
	}
	if (con_player != 1 || con_exit != 1)
		return (false);
	return (true);
}

void	validate_number_elements(t_data *data, int width, int height)
{
	if (data->coll_con == 0)
		exit_ft_printf("[MAP ERROR]The 'C' element is incorrect.", data);
	if (data->player.i == 0 && data->player.j == 0)
		exit_ft_printf("[MAP ERROR]The 'P' element is incorrect.", data);
	if (data->exit.i == 0 && data->exit.j == 0)
		exit_ft_printf("[MAP ERROR]The 'E' element is incorrect.", data);
	if (!is_only_one_p_e(data, data->img, width, height))
		exit_ft_printf("[MAP ERROR]Please only have one 'P' and one 'E'.", \
						data);
}

void	validate_map_format(t_data *data, int width, int height)
{
	validate_number_elements(data, width, height);
	if (!(is_surrounded_walls(data, data->img, width, height)))
		exit_ft_printf("[MAP ERROR]The map is not surrounded by walls.", data);
	if (!can_goal(data, data->map, data->x_row, data->y_column))
		exit_ft_printf("[MAP ERROR] Impossible to reach goal.", data);
}
