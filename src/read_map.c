/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/18 03:29:50 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

void	validate_map(t_data *data, t_img *img, int width, int height)
{
	int	s_x;
	int	s_y;

	s_x = data->player.i;
	s_y = data->player.j;
	if (s_x == 0 || s_y == 0 || s_x == width - 1 || s_y == height - 1)
		exit_ft_printf("[MAP ERROR]The 'P' element is incorrect.");

	if (!(is_surrounded_walls(data->p, data->img, width, height)))
		exit_ft_printf("[MAP ERROR]The map is not surrounded by walls.");

	if (can_goal(data, map, data->x_row, data->y_column))
		free_map(map, data->y_column);
	else
	{
		free_map(map, data->y_column);
		exit_ft_printf("[MAP ERROR] Impossible to reach goal.");
	}

}

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

void	validate_line(t_data *data, char **map, int fd)
{
	char	*line;
	int		i;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
		exit_ft_printf("[MAP ERROR]Map file is empty.");
	j = 0;
	while (line != NULL && line[0] != '\n')
	{
		i = 0;
		while (i >= 0 && line[i] != '\n')
			i = set_map_elements(data, line, i, j);
		if (i < 0)
			exit_ft_printf("[MAP ERROR]There is an invalid character.");
		if (j > 0 && data->x_row != i)
			exit_ft_printf("[MAP ERROR]Not rectangular.");
		map[j] = line;
		data->x_row = i;
		line = get_next_line(fd);
		j++;
	}
	data->y_column = j;
}

void	fill_map(t_data *data, char *filename)
{
	char	**map;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror("[FD ERROR]");
	map = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!map)
		exit_perror("[MALLOC ERROR]");
	validate_line(data, map, fd);
	close(fd);
	if (can_goal(data, map, data->x_row, data->y_column))
		free_map(map, data->y_column);
	else
	{
		free_map(map, data->y_column);
		exit_ft_printf("[MAP ERROR] Impossible to reach goal.");
	}
}
