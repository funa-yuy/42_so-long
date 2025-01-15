/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/15 22:52:59 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	search_loop(t_data *data, t_queue *queue, char **maze, t_pos *pos, int queue_size)
{
	t_pos	*next;
	bool	ret;
	bool	goal;
	int		collect;
	int		x_i;
	int		y_j;

	goal = false;
	collect = data->coll_con;
	while (true)
	{
		/* キューから次の探索候補のマスを取得*/
		next = dequeue(queue, queue_size);
		if (next == NULL)
		{
			ret = false;/* 次の探索候補がない場合は探索失敗 */
			break ;
		}
		x_i = next->i;
		y_j = next->j;

		if (maze[y_j][x_i] == GOAL)
		{
			printf("ゴールに到着\n");
			goal = true;
			if (collect == 0)
			{
				ret = true;
				break ;
			}
		}
		if (maze[y_j][x_i] != PASSED && maze[y_j][x_i] == COLLECTS)
		{
			collect--;
			if (collect == 0 && goal == true)
			{
				ret = true;
				break ;
			}
		}
		maze[y_j][x_i] = PASSED;
		/* 現在探索中のマスから辿れる次の探索候補をキューに格納 */
		if (check(data, maze, x_i, y_j - 1))
		{
			pos->i = x_i;
			pos->j = y_j - 1;
			/* 上方向のマスを探索候補としてキューに格納*/
			enqueue(queue, pos, queue_size);
		}
		if (check(data, maze, x_i, y_j + 1))
		{
			pos->i = x_i;
			pos->j = y_j + 1;
			/* 下方向のマスを探索候補としてキューに格納*/
			enqueue(queue, pos, queue_size);
		}
		if (check(data, maze, x_i - 1, y_j))
		{
			pos->i = x_i - 1;
			pos->j = y_j;
			/* 左方向のマスを探索候補としてキューに格納*/
			enqueue(queue, pos, queue_size);
		}
		if (check(data, maze, x_i + 1, y_j))
		{
			pos->i = x_i + 1;
			pos->j = y_j;
			/* 右方向のマスを探索候補としてキューに格納*/
			enqueue(queue, pos, queue_size);
		}
	}
	return (ret);
}
/* スタート(i,j)からゴールを探索する関数*/
bool	search(t_data *data, t_queue *queue, char **maze, int s_i, int s_j)
{
	t_pos	pos;
	bool	ret;
	int		queue_size;

	queue_size = (data->x_row * data->y_column) + 1;
	/* 次の探索候補としてスタートのマスの情報をキューに格納 */
	if (check(data, maze, s_i, s_j))
	{
		pos.i = s_i; /* スタートのi座標*/
		pos.j = s_j; /* スタートのj座標*/
		enqueue(queue, &pos, queue_size); /* キューにマスの情報を格納*/
	}
	ret = search_loop(data, queue, maze, &pos, queue_size);
	if (queue->data)
	{
		free(queue->data);
		queue->data = NULL;
	}
	return (ret);
}

bool	bfs_search(t_data *data, char **bfs, int x, int	y)
{
	(void)	data;
	bool	check;
	t_queue	queue;

	check = false;
	for (int j=0; j < y; j++)
	{
		ft_printf("%d行目 = {", j);
		for (int i=0; i < x; i++)
	{
		ft_printf("%c, ", bfs[j][i]);
	}
		ft_printf("}\n");
	}
	init_queue(&queue, x, y);

	check = search(data, &queue, bfs, data->player.x, data->player.y);
	if (check)
		ft_printf("ゴールが見つかりました！\n");
	else
		ft_printf("ゴールが見つかりません！\n");

	for (int j=0; j < y; j++)
	{
		printf("%d行目 = {", j);
		for (int i=0; i < x; i++)
	{
		printf("%c, ", bfs[j][i]);
	}
		printf("}\n");
	}
	return (check);
}
