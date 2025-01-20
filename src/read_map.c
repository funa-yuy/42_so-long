/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/20 16:10:50 by mfunakos         ###   ########.fr       */
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

void	exit_during_read(t_data *data, char *line, char *msg, int j)
{
	free(line);
	free_map(data, j);
	exit_ft_printf(msg, data);
}

bool	validate_mapsize(t_data *data, char *line, int i, int j)
{
	if (i < 0)
		exit_during_read(data, line, \
			"[MAP ERROR]There is an invalid character.", j);
	if (j > 0 && data->x_row != i)
		exit_during_read(data, line, \
			"[MAP ERROR]Not rectangular.", j);
	if (i > 100)
		exit_during_read(data, line, \
			"[MAP ERROR]The width of the map must be less than 100.", j);
	if (j > 100)
		exit_during_read(data, line, \
			"[MAP ERROR]The map height must be less than 100.", j);
	return (true);
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
	while (j <= 100 && line != NULL && line[0] != '\n')
	{
		i = 0;
		while (i >= 0 && i <= 100 && line[i] != '\n')
			i = set_map_elements(data, line, i, j);
		validate_mapsize(data, line, i, j);
		map[j] = line;
		data->x_row = i;
		line = get_next_line(fd);
		j++;
	}
	data->y_column = j;
	free(line);
}

void	fill_map(t_data *data, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror("[OPEN ERROR]", data);
	data->map = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!data->map)
		exit_perror("[MALLOC ERROR]", data);
	read_map_line(data, data->map, fd);
	close(fd);
}
