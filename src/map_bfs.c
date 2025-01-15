/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:06:03 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/15 16:29:25 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

/* キューを初期化する関数 */
void initQueue(QUEUE_T *queue, int width, int height){

	/* キューを空に設定 */
	queue->head = 0;
	queue->tail = -1;

	/* キューのサイズを設定 */
	queue->size = (width * height) + 1;

	/* 必要なメモリを確保 */
	queue->data = (POS_T *)malloc(queue->size * sizeof(POS_T));
	if (!queue->data) {
		fprintf(stderr, "メモリ確保に失敗しました\n");
		exit(EXIT_FAILURE);
	}
}

/* ENQUEUEする関数 */
void enqueue(QUEUE_T *queue, POS_T *input, int queue_size){

	/* キューが満杯なら何もせず関数終了 */
	if((queue->tail + 2) % queue_size == queue->head){
		printf("キューが満杯でENQUEUEできません\n");
		return;
	}

	/* データをデータの最後尾の１つ後ろに格納 */
	queue->data[(queue->tail + 1) % queue_size] = *input;

	/* データの最後尾を１つ後ろに移動 */
	queue->tail = (queue->tail + 1) % queue_size;
}

/* DEQUEUEする関数 */
POS_T *dequeue(QUEUE_T *queue, int queue_size){
	POS_T *ret;

	/* キューが空なら何もせずに関数終了 */
	if((queue->tail + 1) % queue_size == queue->head){
		printf("キューが空です\n");
		return NULL;
	}

	/* データの先頭からデータを取得 */
	ret = &(queue->data[queue->head]);

	/* データの先頭を１つ後ろにずらす */
	queue->head = (queue->head + 1) % queue_size;

	/* 取得したデータを返却 */
	return ret;
}

/* (i,j) が通過可能なマスかどうかを確認する関数 */
bool check(t_data *data, char **maze, int x_i, int y_j) {
	// bool ret = true;

	if (x_i < 0 || x_i >= data->x_row || y_j < 0 || y_j >= data->y_column) {
		/* (i,y_j) は迷路外なので通過不可 */
		// ret = false;
		return (false);
	}

	if (maze[y_j][x_i] == WALL) {
		/* (x_i,y_j) は壁なので通過不可 */
		// ret = false;
		return (false);
	}

	if (maze[y_j][x_i] == PASSED) {
		/* (x_i,y_j) は通過済みなので通過不可 */
		// ret = false;
		return (false);
	}

	// return ret;
	return (true);
}


/* スタート(i,j)からゴールを探索する関数*/
bool search(t_data *data, QUEUE_T *queue, char **maze, int s_i, int s_j)
{

	POS_T pos;
	bool ret;
	bool	goal = false;
	int collect = data->coll_con;

	int	queue_size = (data->x_row * data->y_column) + 1;


	/* 次の探索候補としてスタートのマスの情報をキューに格納 */
	if (check(data, maze, s_i, s_j)) {
		pos.i = s_i; /* スタートのi座標*/
		pos.j = s_j; /* スタートのj座標*/

		enqueue(queue, &pos, queue_size); /* キューにマスの情報を格納*/
	}

	while (true) {
		int x_i, y_j;

		/* キューから次の探索候補のマスを取得*/
		POS_T *next = dequeue(queue, queue_size);
		if (next == NULL) {
			/* 次の探索候補がない場合は探索失敗 */
			ret = false;
			break;
		}
		/* 探索するマスの座標を取得 */
		x_i = next->i;
		y_j = next->j;

		if (maze[y_j][x_i] == GOAL) {
			/* 探索対象が見つかったので探索成功 */
			printf("ゴールに到着\n");
			goal = true;
			// break;
			if (collect == 0 && goal == true)
			{
				ret = true;
				break;
			}
		}
		if (maze[y_j][x_i] != PASSED && maze[y_j][x_i] == COLLECTS) {
			/* 探索対象が見つかったので探索成功 */
			// printf("ゴールに到着\n");
			// ret = true;
			collect--;
			if (collect == 0 && goal == true)
			{
				ret = true;
				break;
			}
		}

		/* 探索済みのマスに印をつける */
		maze[y_j][x_i] = PASSED;

		/* 現在探索中のマスから辿れる次の探索候補をキューに格納 */
		if (check(data, maze, x_i, y_j - 1)) {
			/* 上方向に辿れる場合 */

			pos.i = x_i; /* 上方向のマスのi座標 */
			pos.j = y_j - 1; /* 上方向のマスのy_j座標 */

			/* 上方向のマスを探索候補としてキューに格納*/
			enqueue(queue, &pos, queue_size);
		}

		if (check(data, maze, x_i, y_j + 1)) {
			/* 下方向に辿れる場合 */

			pos.i = x_i; /* 下方向のマスのi座標 */
			pos.j = y_j + 1; /* 下方向のマスのy_j座標 */

			/* 下方向のマスを探索候補としてキューに格納*/
			enqueue(queue, &pos, queue_size);
		}

		if (check(data, maze, x_i - 1, y_j)) {
			/* 左方向に辿れる場合 */

			pos.i = x_i - 1; /* 左方向のマスのi座標 */
			pos.j = y_j; /* 左方向のマスのy_j座標 */

			/* 左方向のマスを探索候補としてキューに格納*/
			enqueue(queue, &pos, queue_size);
		}

		if (check(data, maze, x_i + 1, y_j)) {
			/* 右方向に辿れる場合 */
			pos.i = x_i + 1; /* 右方向のマスのi座標 */
			pos.j = y_j; /* 右方向のマスのy_j座標 */

			/* 右方向のマスを探索候補としてキューに格納*/
			enqueue(queue, &pos, queue_size);
		}
	}
	if (queue->data) {
		free(queue->data);
		queue->data = NULL;
	}
	return ret;
}


void	free_map(char **map, int rows)
{
	int	i;

	for (i = 0; i < rows; i++)
		free(map[i]); // 各行を解放
	free(map);         // 配列自体を解放
}


bool	bfs_search(t_data *data, char **bfs, int x, int	y)
{
	(void) data;
	bool cheack;

	cheack = false;
	for (int j=0; j < y; j++){
	ft_printf("%d行目 = {", j);
	for (int i=0; i < x; i++){
		ft_printf("%c, ", bfs[j][i]);
	}
	ft_printf("}\n");
	}

	QUEUE_T queue;
	initQueue(&queue, x, y);

	/* ゴールの位置を設定 */
	// maze[3][3] = GOAL;

	/* スタート位置を(1,3)として開始 */
	cheack = search(data, &queue, bfs, data->player.x, data->player.y);
	if (cheack) {
		ft_printf("ゴールが見つかりました！\n");
	} else {
		ft_printf("ゴールが見つかりません！\n");
	}

	for (int j=0; j < y; j++){
	printf("%d行目 = {", j);
	for (int i=0; i < x; i++){
		printf("%c, ", bfs[j][i]);
	}
	printf("}\n");
	}
	return (cheack);
}
