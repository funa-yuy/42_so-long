/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/18 04:59:22 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	did_search(char **map, t_pos *cur, int *collect, bool *goal)
{
	int	x_i;
	int	y_j;

	x_i = cur->i;
	y_j = cur->j;
	if (map[y_j][x_i] == GOAL)
	{
		*goal = true;
		if (*collect == 0)
			return (true);
	}
	if (map[y_j][x_i] != PASSED && map[y_j][x_i] == COLLECTS)
	{
		(*collect)--;
		if (*collect == 0 && *goal == true)
			return (true);
	}
	return (false);
}

// void	enqueue_next_pos(t_queue *que, t_pos *pos, t_pos *cur)
// {
// 	if (is_passable(data, map, cur->i, cur->j - 1))
// 	{
// 		pos->i = cur->i;
// 		pos->j = cur->j - 1;
// 		enqueue(que, pos);
// 	}
// 	if (is_passable(data, map, cur->i, cur->j + 1))
// 	{
// 		pos->i = cur->i;
// 		pos->j = cur->j + 1;
// 		enqueue(que, pos);
// 	}
// 	if (is_passable(data, map, cur->i - 1, cur->j))
// 	{
// 		pos->i = cur->i - 1;
// 		pos->j = cur->j;
// 		enqueue(que, pos);
// 	}
// 	if (is_passable(data, map, cur->i + 1, cur->j))
// 	{
// 		pos->i = cur->i + 1;
// 		pos->j = cur->j;
// 		enqueue(que, pos);
// 	}
// }

void	enqueue_next_pos(t_queue *que, t_pos *cur)
{
	if (is_passable(data, map, cur->i, cur->j - 1))
		enqueue(que, cur->i, cur - 1);
	if (is_passable(data, map, cur->i, cur->j + 1))
		enqueue(que, cur->i, cur->j + 1);
	if (is_passable(data, map, cur->i - 1, cur->j))
		enqueue(que, cur->i - 1, cur->j);
	if (is_passable(data, map, cur->i + 1, cur->j))
		enqueue(que, cur->i + 1, cur->j);
}

bool	bfs_search(t_data *data, t_queue *que, char **map)
{
	t_pos	*cur;
	bool	goal;
	int		collect;

	goal = false;
	collect = data->coll_con;
	while (true)
	{
		cur = dequeue(que);
		if (cur == NULL)
			return (false);
		if (did_search(map, cur, &collect, &goal))
			return (true);
		map[cur->j][cur->i] = PASSED;
		enqueue_next_pos(que, cur);
	}
	return (false);
}

bool	can_goal(t_data *data, char **map, int x, int y)
{
	bool	ret;
	t_queue	que;
	t_pos	pos;

	ret = false;
	init_queue(data, &que, x, y);
	if (is_passable(data, map, data->player.i, data->player.j))
	{
		pos.i = data->player.i;
		pos.j = data->player.j;
		enqueue(que, pos, data->player.i, data->player.j);
		// enqueue(&que, &pos);
	}
	ret = bfs_search(data, &que, map);
	free_queue(&que);
	return (ret);
}
