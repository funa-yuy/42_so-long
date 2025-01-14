#include <stdio.h>
#include <stdbool.h>

/* 迷路のサイズ */
// #define MEIRO_WIDTH 13
// #define MEIRO_HEIGHT 9
#define MEIRO_WIDTH 5
#define MEIRO_HEIGHT 5

#define PATH 0 /* 通路 */
#define WALL 1 /* 壁 */
#define GOAL 5 /* ゴール */
#define PASSED 3 /* 通過したマス */

/* 管理するデータの上限個数 */
#define MAX_NUM (MEIRO_WIDTH * MEIRO_HEIGHT)

#define QUEUE_SIZE (MAX_NUM + 1)

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
    POS_T data[QUEUE_SIZE];
} QUEUE_T;

QUEUE_T queue;

/* 迷路を表す配列(0:通路、1:壁) */
// static int maze[MEIRO_HEIGHT][MEIRO_WIDTH] =
// {
//     {1,1,1,1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,0,0,0,1,1,1},
//     {1,0,1,1,1,1,1,1,1,0,1,0,1},
//     {1,0,0,0,0,0,0,0,1,0,0,0,1},
//     {1,0,1,1,1,1,1,0,1,1,1,0,1},
//     {1,0,0,0,0,0,0,0,0,0,1,0,1},
//     {1,0,1,0,1,0,1,1,1,0,1,0,1},
//     {1,0,0,0,0,0,0,0,1,0,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

static int maze[MEIRO_HEIGHT][MEIRO_WIDTH] =
{
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,1,0,1},
    {1,1,1,1,1}
};

/* キューを初期化する関数 */
void initQueue(QUEUE_T *queue){

    /* キューを空に設定 */
    queue->head = 0;
    queue->tail = -1;
}

/* ENQUEUEする関数 */
void enqueue(QUEUE_T *queue, POS_T *input){

    /* キューが満杯なら何もせず関数終了 */
    if((queue->tail + 2) % QUEUE_SIZE == queue->head){
        printf("キューが満杯でENQUEUEできません\n");
        return;
    }

    /* データをデータの最後尾の１つ後ろに格納 */
    queue->data[(queue->tail + 1) % QUEUE_SIZE] = *input;

    /* データの最後尾を１つ後ろに移動 */
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;
}

/* DEQUEUEする関数 */
POS_T *dequeue(QUEUE_T *queue){
    POS_T *ret;

    /* キューが空なら何もせずに関数終了 */
    if((queue->tail + 1) % QUEUE_SIZE == queue->head){
        printf("キューが空です\n");
        return NULL;
    }

    /* データの先頭からデータを取得 */
    ret = &(queue->data[queue->head]);

    /* データの先頭を１つ後ろにずらす */
    queue->head = (queue->head + 1) % QUEUE_SIZE;

    /* 取得したデータを返却 */
    return ret;
}

/* (i,j) が通過可能なマスかどうかを確認する関数 */
bool check(int x_i, int y_j) {
    bool ret = true;

    if (x_i < 0 || x_i >= MEIRO_WIDTH || y_j < 0 || y_j >= MEIRO_HEIGHT) {
        /* (i,y_j) は迷路外なので通過不可 */
        ret = false;
    }

    if (maze[y_j][x_i] == WALL) {
        /* (x_i,y_j) は壁なので通過不可 */
        ret = false;
    }

    if (maze[y_j][x_i] == PASSED) {
        /* (x_i,y_j) は通過済みなので通過不可 */
        ret = false;
    }

    return ret;
}


/* スタート(i,j)からゴールを探索する関数*/
bool search(int s_i, int s_j) {

    POS_T pos;
    bool ret;

    /* 次の探索候補としてスタートのマスの情報をキューに格納 */
    if (check(s_i, s_j)) {
        pos.i = s_i; /* スタートのi座標*/
        pos.j = s_j; /* スタートのj座標*/

        enqueue(&queue, &pos); /* キューにマスの情報を格納*/
    }

    while (true) {
        int x_i, y_j;

        /* キューから次の探索候補のマスを取得*/
        POS_T *next = dequeue(&queue);
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
            ret = true;
            break;
        }

        /* 探索済みのマスに印をつける */
        maze[y_j][x_i] = PASSED;

        /* 現在探索中のマスから辿れる次の探索候補をキューに格納 */
        if (check(x_i, y_j - 1)) {
            /* 上方向に辿れる場合 */

            pos.i = x_i; /* 上方向のマスのi座標 */
            pos.j = y_j - 1; /* 上方向のマスのy_j座標 */

            /* 上方向のマスを探索候補としてキューに格納*/
            enqueue(&queue, &pos);
        }

        if (check(x_i, y_j + 1)) {
            /* 下方向に辿れる場合 */

            pos.i = x_i; /* 下方向のマスのi座標 */
            pos.j = y_j + 1; /* 下方向のマスのy_j座標 */

            /* 下方向のマスを探索候補としてキューに格納*/
            enqueue(&queue, &pos);
        }

        if (check(x_i - 1, y_j)) {
            /* 左方向に辿れる場合 */

            pos.i = x_i - 1; /* 左方向のマスのi座標 */
            pos.j = y_j; /* 左方向のマスのy_j座標 */

            /* 左方向のマスを探索候補としてキューに格納*/
            enqueue(&queue, &pos);
        }

        if (check(x_i + 1, y_j)) {
            /* 右方向に辿れる場合 */
            pos.i = x_i + 1; /* 右方向のマスのi座標 */
            pos.j = y_j; /* 右方向のマスのy_j座標 */

            /* 右方向のマスを探索候補としてキューに格納*/
            enqueue(&queue, &pos);
        }
    }

    return ret;
}

int main(void) {

    initQueue(&queue);

    /* ゴールの位置を設定 */
    maze[3][3] = GOAL;

    /* スタート位置を(1,3)として開始 */
    if (search(1, 1)) {
        printf("ゴールが見つかりました！\n");
    } else {
        printf("ゴールが見つかりません！\n");
    }
	for (int j=0; j < MEIRO_HEIGHT; j++){
		printf("%d行目 = {", j);
		for (int i=0; i < MEIRO_WIDTH; i++){
			printf("%d, ", maze[j][i]);
		}
		printf("}\n");
	}

    return 0;
}
