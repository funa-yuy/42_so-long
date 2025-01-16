/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 04:21:24 by miyuu            ###   ########.fr       */
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
		if (data->p[0][i] != img->wall_img || data->p[y - 1][i] != img->wall_img)
			return (error_ft_printf("The map is not surrounded by walls."));
		i++;
	}
	i = 0;
	while (i < y)
	{
		if (data->p[i][0] != img->wall_img || data->p[i][x - 1] != img->wall_img)
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

void	read_map(t_data *data, t_img *img, char *filename)
{
	char	*line;
	int		i;
	int		j;
	char	**map;

	map = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!map)
		exit(1);
	j = 0;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		error_ft_printf("No such file or directory.");
	line = get_next_line(data->fd);
	if (line == NULL)
		error_ft_printf("Map file is empty.");
	while (line != NULL && line[0] != '\n')
	{
		i = 0;
		while (line[i] != '\n')
		{
			if (line[i] == PATH)
				data->p[j][i] = img->em_img;
			else if (line[i] == WALL)
				data->p[j][i] = img->wall_img;
			else if (line[i] == COLLECTS)
			{
				data->p[j][i] = img->col_img;
				data->coll_con++;
				ft_printf(" %d coll\n", data->coll_con);
			}
			else if (line[i] == GOAL)
				data->p[j][i] = img->exit_img;
			else if (line[i] == 'P')
			{
				data->p[j][i] = img->p_img;
				data->player = (t_player){i, j};
			}
			else
				error_ft_printf("There is an invalid character.");
			i++;
		}
		if (j > 0 && data->x_row != i)
		{
			ft_printf("Error\nNot rectangular\n");
			exit(1);
		}
		else
			data->x_row = i;
		map[j] = line;
		// free(line);
		line = get_next_line(data->fd);
		j++;
	}
	data->y_column = j;
	// free(line);
	close(data->fd);

	if (can_goal(data, map,  data->x_row, j))
		free_map(map, j);
	else
	{
		free_map(map, j);
		error_ft_printf("The goal was not found.");
	}
}
