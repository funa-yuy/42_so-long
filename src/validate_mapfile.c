/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_mapfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:29:13 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/21 21:01:00 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	validate_extension(char *filename)
{
	size_t	i;

	i = ft_strlen(filename) - 1;
	if (i > 4 && filename[i - 4] != '/')
	{
		if (filename[i - 3] == '.' && filename[i - 2] == 'b' \
			&& filename[i - 1] == 'e' && filename[i] == 'r')
			return (true);
	}
	return (false);
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
	if (i > MAX_MAP)
		exit_during_read(data, line, \
			"[MAP ERROR]The width of the map must be less than 100.", j);
	return (true);
}
