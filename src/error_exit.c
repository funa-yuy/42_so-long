/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 20:20:52 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/19 22:11:24 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	exit_ft_printf(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	free_data(data);
	exit(EXIT_FAILURE);
}

int	exit_perror(char *msg, t_data *data)
{
	perror(msg);
	free_data(data);
	exit(EXIT_FAILURE);
}
