/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/17 20:38:48 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	process_goal_collect(char **map, t_pos *cur, int *collect, bool *goal)
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

void	next_pos(t_queue *que, t_pos *pos, int x, int y)
{
	pos->i = x;
	pos->j = y;
	enqueue(que, pos);
}

bool	bfs_search(t_data *data, t_queue *que, char **map, t_pos *pos)
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
		if (process_goal_collect(map, cur, &collect, &goal))
			return (true);
		map[cur->j][cur->i] = PASSED;
		if (check(data, map, cur->i, cur->j - 1))
			next_pos(que, pos, cur->i, cur->j - 1);
		if (check(data, map, cur->i, cur->j + 1))
			next_pos(que, pos, cur->i, cur->j + 1);
		if (check(data, map, cur->i - 1, cur->j))
			next_pos(que, pos, cur->i - 1, cur->j);
		if (check(data, map, cur->i + 1, cur->j))
			next_pos(que, pos, cur->i + 1, cur->j);
	}
	return (false);
}

bool	can_goal(t_data *data, char **map, int x, int y)
{
	bool	ret;
	t_queue	que;
	t_pos	pos;

	ret = false;
	init_queue(&que, x, y);
	if (check(data, map, data->player.i, data->player.j))
	{
		pos.i = data->player.i;
		pos.j = data->player.j;
		enqueue(&que, &pos);
	}
	ret = bfs_search(data, &que, map, &pos);
	if (que.data)
	{
		free(que.data);
		que.data = NULL;
	}
	return (ret);
}
