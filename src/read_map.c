/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 05:22:44 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_error_cheack(t_data *data, int x, int y, t_img *img)
{
	int		i;
	int		s_x;
	int		s_y;

	s_x = data->player.x ;
	s_y = data->player.y;
	if (s_x == 0 || s_y == 0 || s_x == x -1 || s_y == y -1)
		return (error_ft_printf("The 'P' element is incorrect.\n"));
	i = 0;
	while (i < x)
	{
		if (data->p[0][i] != img->wall_img || \
			data->p[y - 1][i] != img->wall_img)
			return (error_ft_printf("The map is not surrounded by walls."));
		i++;
	}
	i = 0;
	while (i < y)
	{
		if (data->p[i][0] != img->wall_img || \
			data->p[i][x - 1] != img->wall_img)
			return (error_ft_printf("The map is not surrounded by walls."));
		i++;
	}
	return (0);
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

int	set_line(t_data *data, t_img *img, int i, int j)
{
	while (line[i] != '\n')
	{
		if (line[i] == EMPTY)
			data->p[j][i] = img->em_img;
		else if (line[i] == WALL)
			data->p[j][i] = img->wall_img;
		else if (line[i] == COLLECTS)
		{
			data->p[j][i] = img->col_img;
			data->coll_con++;
		}
		else if (line[i] == GOAL)
			data->p[j][i] = img->exit_img;
		else if (line[i] == 'P')
		{
			data->p[j][i] = img->p_img;
			data->player = (t_player){i, j};
		}
		else
			return (-1);
		i++;
	}
	return (i);
}

void	validate_line(t_data *data, t_img *img, char **map, size_t fd)
{
	char	*line;
	int		i;
	int		j;

	line = get_next_line(fd);
	if (line == NULL)
		error_ft_printf("Map file is empty.");
	j = 0;
	while (line != NULL && line[0] != '\n')
	{
		i = set_line(data, img, 0, j);
		if (i < 0)
		{
			free_map(map, j);
			error_ft_printf("There is an invalid character.");
		}
		if (j > 0 && data->x_row != i)
			error_ft_printf("Not rectangular.");
		data->x_row = i;
		map[j] = line;
		line = get_next_line(fd);
		j++;
	}
	data->y_column = j;
}

void	read_map(t_data *data, t_img *img, char *filename)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!map)
		exit(1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_ft_printf("No such file or directory.");
	validate_line(data, img, map, fd);
	close(fd);
	if (can_goal(data, map, data->x_row, data->y_column))
		free_map(map, data->y_column);
	else
	{
		free_map(map, data->y_column);
		error_ft_printf("The goal was not found.");
	}
}
