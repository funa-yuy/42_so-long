/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:54:51 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/18 03:04:52 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*read_img(void *mlx, char *filename)
{
	int		fd;
	int		size;
	void	*img;

	size = IMG_SIZE;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_perror("[FD ERROR]");
	close(fd);
	img = mlx_xpm_file_to_image(mlx, filename, &size, &size);
	if (!img)
		exit_ft_printf("Failed create image file.");
	return (img);
}

void	fill_img(t_data *data, t_img *img)
{
	img->em_img = read_img(data->mlx, "textures/empty.xpm");
	img->wall_img = read_img(data->mlx, "textures/wall.xpm");
	img->col_img = read_img(data->mlx, "textures/collects.xpm");
	img->exit_img = read_img(data->mlx, "textures/exit.xpm");
	img->p_img = read_img(data->mlx, "textures/souzou_got_01.xpm");
}
