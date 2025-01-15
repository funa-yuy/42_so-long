/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/15 16:26:45 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	map_error_cheack(t_data *data, int x, int y, t_img *img)
{
	int		i;

	if (data->player.x == 0 || data->player.y == 0 || data->player.x == x -1 || data->player.y == y -1)
	{
		ft_printf("The 'P' element is incorrect.\n");
		return (-1);
	}

	i = 0;
	while (i < x)
	{
		if (data->p[0][i] != img->wall_img || data->p[y - 1][i] != img->wall_img)
		{
			ft_printf("The map is not surrounded by walls.\n");
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < y)
	{
		if (data->p[i][0] != img->wall_img || data->p[i][x-1] != img->wall_img)
		{
			ft_printf("The map is not surrounded by walls.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

// int	map_error_cheack(t_data *data, int x, int y, t_img *img)
// {
// 	int		i;

// 	char		**s;

// 	s[y][x] = 0;

// 	i = 0;
// 	while ()
// 	{
// 		if (p[y][i + 1] == img->wall_img)
// 			p[y][i + 1] = s[y][i] + 1;
// 		if (p[y][i - 1] == img->wall_img)
// 			p[y][i - 1] = s[y][i] + 1;
// 		if (p[y + 1][i] == img->wall_img)
// 			p[y + 1][i] = s[y][i] + 1;
// 		if (p[y - i][i] == img->wall_img)
// 			p[y - i][i] = s[y][i] + 1;
// 		i++;
// 	}
// 	return (0);
// }



void	read_map(t_data *data, t_img *img, char *filename)
{
	char	*line;
	int		i;
	int		j;
	char	**bfs;

	bfs = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!bfs)
		exit(1);
	j = 0;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
	{
		ft_printf("Error\nNo such file or directory\n");
		exit(1);
	}
	line = get_next_line(data->fd);
	if (line == NULL)
	{
		ft_printf("Map file is empty.\n");
		exit(1);
	}
	while (line != NULL && line[0] != '\n')
	{
		i = 0;
		while (line[i] != '\n')
		{
			if (line[i] == '0')
				data->p[j][i] = img->em_img;
			else if (line[i] == '1')
				data->p[j][i] = img->wall_img;
			else if (line[i] == 'C')
			{
				data->p[j][i] = img->col_img;
				data->coll_con++;
				ft_printf(" %d coll\n", data->coll_con);
			}
			else if (line[i] == 'E')
				data->p[j][i] = img->exit_img;
			else if (line[i] == 'P')
			{
				data->p[j][i] = img->p_img;
				data->player = (t_player){i, j};
			}
			else
			{
				ft_printf("There is an invalid character '%c'.\n", line[i]);
				exit(1);
			}
			i++;
		}
		if (j > 0 && data->x_row != i)
		{
			ft_printf("Error\nNot rectangular\n");
			exit(1);
		}
		else
			data->x_row = i;
		bfs[j] = line;
		// free(line);
		line = get_next_line(data->fd);
		j++;
	}
	data->y_column = j;
	// free(line);
	close(data->fd);


	if (bfs_search(data, bfs,  data->x_row, j))
		free_map(bfs, j);
	else
	{
		ft_printf("ゴールが見つかりません！\n");
		free_map(bfs, j);
		exit (1);
	}
}
