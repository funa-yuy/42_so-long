/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:54:51 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 18:46:22 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	*load_img_in_mlx(void *mlx, char *filename)
{
	int		fd;
	int		size;
	void	*img;

	size = IMG_SIZE;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_ft_printf("No exist image file.");
	close(fd);
	img = mlx_xpm_file_to_image(mlx, filename, &size, &size);
	if (!img)
		exit_ft_printf("Failed create image file.");
	return (img);
}

void	read_img(t_data *data, t_img *img)
{
	img->em_img = load_img_in_mlx(data->mlx, "textures/empty.xpm");
	img->wall_img = load_img_in_mlx(data->mlx, "textures/wall.xpm");
	img->col_img = load_img_in_mlx(data->mlx, "textures/collects.xpm");
	img->exit_img = load_img_in_mlx(data->mlx, "textures/exit.xpm");
	img->p_img = load_img_in_mlx(data->mlx, "textures/souzou_got_01.xpm");
}
