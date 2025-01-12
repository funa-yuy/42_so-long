/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:48:38 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/12 18:38:24 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


void	read_map(t_data *data, t_img *img, char *filename)
{
	char	*line;
	int		i;
	int		j;

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
		while (line[i] != '\0')
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
			// else
			// {
			// 	ft_printf("There is an invalid character.\n");
			// 	exit(1);
			// }
			i++;
		}
		// if (j > 0 && data->x_row != --i)
		// {
		// 	ft_printf("Error\nNot rectangular\n");
		// 	exit(1);
		// }
		data->x_row = --i;
		free(line);
		line = get_next_line(data->fd);
		j++;
	}
	data->y_column = j;
	free(line);
	close(data->fd);
}
