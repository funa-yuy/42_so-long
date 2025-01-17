/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/17 22:57:55 by mfunakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


// TODO: add cleanup
int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	disply_img(t_data *data, void *p_img[MAX_MAP][MAX_MAP])
{
	int		x;
	int		y;

	y = 0;
	while (y < data->y_column)
	{
		x = 0;
		while (x < data->x_row)
		{
			mlx_put_image_to_window(data->mlx, data->win, p_img[y][x], \
				IMG_SIZE * x, IMG_SIZE * y);
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data, t_img *img)
{
	img->em_img = NULL;
	img->wall_img = NULL;
	img->col_img = NULL;
	img->exit_img = NULL;
	img->p_img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = img;
	data->count = 1;
	data->coll_con = 0;
	data->y_column = 0;
	data->x_row = 0;
	data->player.i = 0;
	data->player.j = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;
	// dataの読み込み
	if (argc != 2)
		exit_ft_printf("Check number of arguments.");
	init_data(&data, &img);
	data.mlx = mlx_init();
	read_img(&data, &img);
	read_map(&data, argv[1]);

	// mapのvalidate
	map_error_cheack(&data, data.x_row, data.y_column, &img);

	// ゲーム画面の表示
	data.win = mlx_new_window(data.mlx, data.x_row * IMG_SIZE, \
		data.y_column * IMG_SIZE, "so_long");
	disply_img(&data, data.p);

	// 操作の設定
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, window_close, &data);
	mlx_key_hook(data.win, key_push, &data);
	mlx_loop(data.mlx);
}

/*
POINT:
1. 一つの関数に一つの仕事
2. 関数の命名は {動詞_名詞}

	data filter_male(data)
	->あいまいな動詞は解釈が分かれるためNG
	data exclude_male(data)
	->男性以外のデータが残ることが明確なのでOK
*/

/*
STEP:
funa
1. データの読み込み
	a : mapファイルをopen
	b : mapファイルをread
	c : mapファイルを構造体に格納
	d : imageのファイルを構造体に格納
	e : mlxの構造体を初期化
2. mapのvalidate
	a : goalできるか
	b : pあるか
	(..) : ...
3. ゲーム画面の表示
	a : winを表示
	b : winにxpmファイルをプットする
4. 操作の設定
	a : 終了条件ESC
	b : 終了条件☓
	c : player移動
		(0) : wasdに移動を割当する
		(1) : 収集物をすべて取得したか判定する
		(2) : ゴールに到達したか判定する
		(3) : (1), (2)を同時に満たした場合終了する
*/

/*
int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;

	// 引数が正しくない場合を弾く
	if (argc != 2)
		exit_ft_printf("Check number of arguments.");
	// 構造体の初期化
	init_data(&data, &img);
	// mlxの初期化
	data.mlx = mlx_init();

	// 画像の読み込みと構造体への格納
	read_img(&data, &img);
	// マップの読み込みとゴールが可能かのチェック // TODO: separate this func
	read_map(&data, argv[1]);
	// マップのP、E,Cの数が不正かのチェック
	map_error_cheack(&data, data.x_row, data.y_column, &img);

	// window描画
	data.win = mlx_new_window(data.mlx, data.x_row * IMG_SIZE, \
		data.y_column * IMG_SIZE, "so_long");
	// windowにimageをputする
	disply_img(&data, data.p);

	// mlxのお作法
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, window_close, &data);
	mlx_key_hook(data.win, key_push, &data);
	mlx_loop(data.mlx);
}
*/
