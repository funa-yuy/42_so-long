/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mac.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:59:33 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/15 15:34:05 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include <X11/keysym.h>
// #include <X11/X.h>

#include <string.h>//strchr用

#include "./lib/get_next_line/get_next_line.h"


# define T_SIZE 32
# define MAX_MAP	1000

typedef struct s_player
{
	int			x;
	int			y;
}			t_player;


typedef struct s_img{
	char	**repo;
	char	**fill;
	int	empty;//敵の数
	int	wall;//数
	int	collects;//数
	int	exit;//数
	int	player;//数
	void	*em_img;
	void	*wall_img;
	void	*col_img;
	void	*exit_img;
	void	*p_img;
}				t_img;

typedef struct	s_data {
	void	*mlx;
	void	*win;
	t_img	*img;
	int		fd;
	char	*addr;
	int			coll_con;
	int			y_column;//列(縦軸)
	int			x_row;//行(横軸)
	t_player	player;
}				t_data;

#include <stdio.h>
#include <stdbool.h>

/* 迷路のサイズ */
// #define MEIRO_WIDTH 13
// #define MEIRO_HEIGHT 9
#define MEIRO_WIDTH 6
#define MEIRO_HEIGHT 5



#define PATH '0' /* 通路 */
#define WALL '1' /* 壁 */
#define GOAL 'E' /* ゴール */
#define COLLECTS 'C' /* ゴール */
#define PASSED '3' /* 通過したマス */

/* 管理するデータの上限個数 */
// #define MAX_NUM (MEIRO_WIDTH * MEIRO_HEIGHT)

// #define QUEUE_SIZE (MAX_NUM + 1)

/* マスの位置情報 */
typedef struct POS {
	int i; /* マスのi座標 */
	int j; /* マスのj座標 */
} POS_T;

/* キュー構造体 */
typedef struct QUEUE {
	 /* データの最後尾 */
	 int tail;
	 /* データの先頭 */
	 int head;
	 /* キューされているデータ */
	 POS_T *data;
	 int size;
}			QUEUE_T;

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

	return ret;
}


void	free_map(char **map, int rows)
{
	int	i;

	for (i = 0; i < rows; i++)
		free(map[i]); // 各行を解放
	free(map);         // 配列自体を解放
}


void	bfs_search(t_data *data, char **bfs, int x, int	y)
{
	for (int j=0; j < y; j++){
	printf("%d行目 = {", j);
	for (int i=0; i < x; i++){
		printf("%c, ", bfs[j][i]);
	}
	printf("}\n");
	}

	QUEUE_T queue;
	initQueue(&queue, x, y);

	/* ゴールの位置を設定 */
	// maze[3][3] = GOAL;

	/* スタート位置を(1,3)として開始 */
	if (search(data, &queue, bfs, data->player.x, data->player.y)) {
		printf("ゴールが見つかりました！\n");
	} else {
		printf("ゴールが見つかりません！\n");
	}
	if (queue.data) {
		free(queue.data);
		queue.data = NULL;
	}
	for (int j=0; j < y; j++){
	printf("%d行目 = {", j);
	for (int i=0; i < x; i++){
		printf("%c, ", bfs[j][i]);
	}
	printf("}\n");
	}

}

void	img_disply(int *components, void	*img, int x, int y, char s)
{
	(void)img;
	// mlx_put_image_to_window(data->mlx, data->win, img, T_SIZE * x, T_SIZE * y);
	(*components)++;
	// printf("%c 合計:%d x:%d y:%d \n", s, *components, T_SIZE * x, T_SIZE * y);
}

void	read_map(t_data *data, char *filename)
{
	char	*line;
	int	i;
	int	j;
	char	**bfs;
	bfs = (char **)malloc(sizeof(char *) * MAX_MAP);
	if (!bfs)
		exit(1);
	data->coll_con= 0;
	j = 0;
	data->fd = open(filename, O_RDONLY);
	if (data->fd < 0)
		printf("Error\nNo such file or directory\n");
	line = get_next_line(data->fd);
	if (line == NULL)
		printf("Map file is empty.");
	while (line != NULL && line[0] != '\n')
	{
		// printf("player : %d\n", data->img->player);
		i = 0;
		while(line[i] != '\n')
		{
			if (line[i] == '0')
				img_disply(&data->img->empty, data->img->em_img, j, i, line[i]);
			else if (line[i] == '1')
				img_disply(&data->img->wall, data->img->wall_img, j, i, line[i]);
			else if (line[i] == 'C')
			{
				img_disply(&data->img->collects, data->img->col_img, j, i, line[i]);
				data->coll_con++;
			}
			else if (line[i] == 'E')
				img_disply(&data->img->exit, data->img->exit_img, j, i, line[i]);
			else if (line[i] == 'P')
			{
				img_disply(&data->img->player, data->img->p_img, j, i, line[i]);
				// data->p[j][i] = img->p_img;
				data->player = (t_player){i, j};
			}
			i++;
		}
		char *newline_pos = strchr(line, '\n');
   		if (newline_pos)
      	  *newline_pos = '\0'; // 改行を終端文字に置き換える
		bfs[j] = line;
		// printf("%s", bfs[j]);
		// printf("\n");
		data->x_row = i;
		// free(line);
		line = get_next_line(data->fd);
		j++;
	}
	close(data->fd);
	data->y_column = j;
	// free(line);

	bfs_search(data, bfs,  data->x_row, j);

	free_map(bfs, j);
}

int	main(int argc, char **argv)
{
	(void)argc;
	// void	*mlx;
	t_data	data;
	t_img   img = {0};  // 全てのメンバを0で初期化
	// void	*mlx_win;

//画像の読み込み
	data.img = &img;
	// read_img(&data, &img);
//MAPの読み込み
	read_map(&data, argv[1]);
	// printf("empty = %d\n", data.img->empty);
	// printf("wall = %d\n", data.img->wall);
	// printf("collects = %d\n", data.img->collects);
	// printf("exit = %d\n", data.img->exit);
	// printf("player = %d\n", data.img->player);
	// printf("y_column = %d\n", data.img->y_column);
	// printf("x_row = %d\n", data.img->x_row);
	// my_mlx_put_map(&data);
	return (0);
}
