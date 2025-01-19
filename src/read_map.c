/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/19 20:48:38 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	set_map_elements(t_data *data, char *line, int i, int j)
{
	if (line[i] == EMPTY)
		data->p[j][i] = data->img->em_img;
	else if (line[i] == WALL)
		data->p[j][i] = data->img->wall_img;
	else if (line[i] == COLLECTS)
	{
		data->p[j][i] = data->img->col_img;
		data->coll_con++;
	}
	else if (line[i] == GOAL)
	{
		data->p[j][i] = data->img->exit_img;
		data->exit = (t_pos){i, j};
	}
	else if (line[i] == 'P')
	{
		data->p[j][i] = data->img->p_img;
		data->player = (t_pos){i, j};
	}
	else
		return (-1);
	return (++i);
}

void	error_during_read(t_data *data, char *line, char *msg, int j)
{
	free(line);
	free_map(data, j);
	exit_ft_printf(msg, data);
}

void	read_map_line(t_data *data, char **map, int fd)
{
	char	*line;
	int		i;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
		exit_ft_printf("[MAP ERROR]Map file is empty.", data);
	j = 0;
	while (line != NULL && line[0] != '\n')
	{
		i = 0;
		while (i >= 0 && line[i] != '\n')
			i = set_map_elements(data, line, i, j);
		if (i < 0)
			error_during_read(data, line, \
				"[MAP ERROR]There is an invalid character.", j);
		if (j > 0 && data->x_row != i)
			error_during_read(data, line, "[MAP ERROR]Not rectangular.", j);
		map[j] = line;
		data->x_row = i;
		// printf("read_map_line:%s", map[j]);
		line = get_next_line(fd);
		j++;
	}
	data->y_column = j;
	free(line);
}

void	fill_map(t_data *data, char *filename)
{
	// char	**map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror("[FD ERROR]", data);
	// data->map = map;
	data->map = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!data->map)
		exit_perror("[MALLOC ERROR]", data);
	read_map_line(data, data->map, fd);
	close(fd);
}

	// if (can_goal(data, map, data->x_row, data->y_column))
	// 	free_map(map, data->y_column);
	// else
	// {
	// 	free_map(map, data->y_column);
	// 	exit_ft_printf("[MAP ERROR] Impossible to reach goal.", data);
	// }
