/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:20:13 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/18 04:19:08 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_queue(t_queue *que)
{
	if (que->wait_que)
	{
		free(que->wait_que);
		que->wait_que = NULL;
	}
}

void	init_queue(t_queue *que, int width, int height)
{
	que->head = 0;
	que->tail = -1;
	que->max_size = (width * height) + 1;
	que->wait_que = (t_pos *)malloc(que->max_size * sizeof(t_pos));
	if (!que->wait_que)
		exit_perror("[MALLOC ERROR]");
}

// void	enqueue(t_queue *que, t_pos *input)
void	enqueue(t_queue *que, int i, int j)
{
	if ((que->tail + 2) % que->max_size == que->head)
		return ;
	// que->wait_que[(que->tail + 1) % que->max_size] = *input;
	que->wait_que[(que->tail + 1) % que->max_size] = (t_pos){i, j};
	que->tail = (que->tail + 1) % que->max_size;
}

t_pos	*dequeue(t_queue *que)
{
	t_pos	*output;

	if ((que->tail + 1) % que->max_size == que->head)
		return (NULL);
	output = &(que->wait_que[que->head]);
	que->head = (que->head + 1) % que->max_size;
	return (output);
}

bool	is_passable(t_data *data, char **map, int x_i, int y_j)
{
	if (x_i < 0 || x_i >= data->x_row || y_j < 0 || y_j >= data->y_column)
		return (false);
	if (map[y_j][x_i] == WALL)
		return (false);
	if (map[y_j][x_i] == PASSED)
		return (false);
	return (true);
}
