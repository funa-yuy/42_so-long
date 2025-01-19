/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:20:52 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/19 20:47:45 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_img(t_data *data, t_img *img)
{
	(void)data;
	if (img->em_img)
		mlx_destroy_image(data->mlx, img->em_img);
		// free(img->em_img);
	if (img->wall_img)
		mlx_destroy_image(data->mlx, img->wall_img);
		// free(img->wall_img);
	if (img->col_img)
		mlx_destroy_image(data->mlx, img->col_img);
		// free(img->col_img);
	if (img->exit_img)
		mlx_destroy_image(data->mlx, img->exit_img);
		// free(img->exit_img);
	if (img->p_img)
		mlx_destroy_image(data->mlx, img->p_img);
		// free(img->p_img);
}

int	exit_ft_printf(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	if (data->map != NULL)
		free_map(data, data->y_column);
	// free(data->map);
	if (data->img)
		free_img(data, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(EXIT_FAILURE);
}

int	exit_perror(char *msg, t_data *data)
{
	perror(msg);
	if (data->map != NULL)
		free_map(data, data->y_column);
	if (data->img)
		free_img(data, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(EXIT_FAILURE);
}
