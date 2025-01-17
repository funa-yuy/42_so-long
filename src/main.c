/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:43:29 by mfunakos          #+#    #+#             */
/*   Updated: 2025/01/18 03:27:52 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"


// TODO: add cleanup
// void	free_double_pointer(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->map->map[i])
// 		i++;
// 	while (i >= 0)
// 		free(data->map->map[i--]);
// 	free(data->map->map);
// 	free(data->img);
// }
// void	handle_error(t_data *data, char *str, int num)
// {
// 	if (num)
// 		free_double_pointer(data);
// 	ft_putstr_fd(str, 2);
// 	exit(EXIT_FAILURE);
// }

// int	ft_exit(t_data *data)
// {
// 	mlx_destroy_window(data->mlx, data->win);
// 	printf("--------------------------------------------------\n");
// 	printf("|              You gave up :(                    |\n");
// 	printf("|   Is the game hard for you? Try again......    |\n");
// 	printf("--------------------------------------------------\n");
// 	free_double_pointer(data);
// 	exit(EXIT_SUCCESS);
// }
int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->img);
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

int	main(int argc, char **argv)
{
	t_data	data;
	t_img	img;
	// dataの読み込み
	if (argc != 2)
		exit_ft_printf("Check number of arguments.");
	fill_data(&data, &img, argv[1]);

	// mapのvalidate
	validate_map(&data, &img, data.x_row, data.y_column);

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
	validate_map(&data, data.x_row, data.y_column, &img);

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
