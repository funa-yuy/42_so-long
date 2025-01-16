/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/17 05:26:32 by miyuu            ###   ########.fr       */
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
			next_pos(data, que, cur->i, cur->j - 1);
		if (check(data, map, cur->i, cur->j + 1))
			next_pos(data, que, cur->i, cur->j + 1);
		if (check(data, map, cur->i - 1, cur->j))
			next_pos(data, que, cur->i - 1, cur->j);
		if (check(data, map, cur->i + 1, cur->j))
			next_pos(data, que, cur->i + 1, cur->j);
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
	if (check(data, map, data->player.x, data->player.y))
	{
		pos.i = data->player.x;
		pos.j = data->player.y;
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

// bool	bfs(t_data *data, t_queue *que, char **map, int s_i, int s_j)
// {
// 	t_pos	pos;
// 	bool	ret;

// 	if (check(data, map, s_i, s_j))
// 	{
// 		pos.i = s_i;
// 		pos.j = s_j;
// 		enqueue(que, &pos);
// 	}
// 	ret = bfs_search(data, que, map, &pos);
// 	if (que->data)
// 	{
// 		free(que->data);
// 		que->data = NULL;
// 	}
// 	return (ret);
// }

// bool	can_goal(t_data *data, char **bfs, int x, int y)
// {
// 	bool	check;
// 	t_queue	que;

// 	check = false;
// 	init_queue(&que, x, y);

// 	check = bfs(data, &que, bfs, data->player.x, data->player.y);
// 	return (check);
// }

// bool	can_goal(t_data *data, char **bfs, int x, int	y)
// {
// 	(void)	data;
// 	bool	check;
// 	t_queue	que;

// 	check = false;
// 	for (int j=0; j < y; j++)
// 	{
// 		ft_printf("%d行目 = {", j);
// 		for (int i=0; i < x; i++)
// 	{
// 		ft_printf("%c, ", bfs[j][i]);
// 	}
// 		ft_printf("}\n");
// 	}
// 	init_queue(&que, x, y);

// 	check = bfs(data, &que, bfs, data->player.x, data->player.y);
// 	if (check)
// 		ft_printf("ゴールが見つかりました！\n");
// 	else
// 		ft_printf("ゴールが見つかりません！\n");

// 	for (int j=0; j < y; j++)
// 	{
// 		printf("%d行目 = {", j);
// 		for (int i=0; i < x; i++)
// 	{
// 		printf("%c, ", bfs[j][i]);
// 	}
// 		printf("}\n");
// 	}
// 	return (check);
// }
