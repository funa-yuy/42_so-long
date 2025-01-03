/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/03 17:26:38 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	t_data	img;
	void	*mlx_win;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 500, 500);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	img.addr[0] = 0xFFFFFFFF;
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	// my_mlx_pixel_put(&img, 50, 50, 0xFFFFFF);
	// my_mlx_pixel_put(&img, 10, 10, 0x00FF00);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 10, 10);
	mlx_loop(mlx);
}
