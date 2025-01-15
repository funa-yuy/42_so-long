/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:20:13 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/15 19:20:41 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* キューを初期化する関数 */
void	initQueue(t_queue *queue, int width, int height)
{
	queue->head = 0;	/* キューを空に設定 */
	queue->tail = -1;
	queue->size = (width * height) + 1;/* キューのサイズを設定 */
	queue->data = (t_pos *)malloc(queue->size * sizeof(t_pos));	/* 必要なメモリを確保 */
	if (!queue->data)
	{
		fprintf(stderr, "メモリ確保に失敗しました\n");
		exit(EXIT_FAILURE);
	}
}

/* ENQUEUEする関数 */
void	enqueue(t_queue *queue, t_pos *input, int queue_size)
{
	if((queue->tail + 2) % queue_size == queue->head)	/* キューが満杯なら何もせず関数終了 */
	{
		ft_printf("キューが満杯でENQUEUEできません\n");
		return ;
	}
	queue->data[(queue->tail + 1) % queue_size] = *input;/* データをデータの最後尾の１つ後ろに格納 */
	queue->tail = (queue->tail + 1) % queue_size;/* データの最後尾を１つ後ろに移動 */
}

/* DEQUEUEする関数 */
t_pos	*dequeue(t_queue *queue, int queue_size)
{
	t_pos	*ret;

	if((queue->tail + 1) % queue_size == queue->head)	/* キューが空なら何もせずに関数終了 */
		return (NULL);
	ret = &(queue->data[queue->head]);	/* データの先頭からデータを取得 */
	queue->head = (queue->head + 1) % queue_size;	/* データの先頭を１つ後ろにずらす */
	return (ret);
}

/* (i,j) が通過可能なマスかどうかを確認する関数 */
bool	check(t_data *data, char **maze, int x_i, int y_j)
{
	if (x_i < 0 || x_i >= data->x_row || y_j < 0 || y_j >= data->y_column);
		return (false);
	if (maze[y_j][x_i] == WALL)
		return (false);
	if (maze[y_j][x_i] == PASSED)
		return (false);

	return (true);
}
