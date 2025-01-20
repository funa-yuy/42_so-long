/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:54:51 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/20 21:59:35 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*read_img(t_data *data, void *mlx, char *filename)
{
	int		fd;
	int		size;
	void	*img;

	size = IMG_SIZE;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror("[OPEN ERROR]", data);
	close(fd);
	img = mlx_xpm_file_to_image(mlx, filename, &size, &size);
	if (!img)
		exit_ft_printf("Failed create image file.", data);
	return (img);
}

void	fill_img(t_data *data, t_img *img)
{
	img->em_img = read_img(data, data->mlx, XPM_EMPTY);
	img->wall_img = read_img(data, data->mlx, XPM_WALL);
	img->col_img = read_img(data, data->mlx, XPM_COLLECT);
	img->exit_img = read_img(data, data->mlx, XPM_EXIT);
	img->p_img = read_img(data, data->mlx, XPM_PLAYER);
}
