/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:13:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/17 05:21:19 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* header*/
# include "get_next_line.h"
# include "ft_printf.h"

/* mlx library */
# include <mlx.h>

/* library */
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <stdbool.h>//bfs

/* define */
# define IMG_SIZE	32
# define MAX_MAP	1000

# define EMPTY	'0'
# define WALL	'1'
# define GOAL	'E'
# define COLLECTS	'C'
# define PASSED	'3'

/* struct */
typedef struct s_player
{
	int			x;
	int			y;
}			t_player;

typedef struct s_img
{
	void	*em_img;
	void	*wall_img;
	void	*col_img;
	void	*exit_img;
	void	*p_img;
}				t_img;

typedef struct s_dat
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			count;
	int			coll_con;
	int			y_column;//列(縦軸)
	int			x_row;//行(横軸)
	void		*p[MAX_MAP][MAX_MAP];
	t_player	player;
}				t_data;

/* マスの位置情報 */
typedef struct pos
{
	int	i;
	int	j;
}				t_pos;

typedef struct queue
{
	int		tail;
	int		head;
	t_pos	*data;
	int		max_size;
}			t_queue;

/* init struct */
void	init_data(t_data *data, t_img *img);

/* read map&img */
void	read_img(t_data *data, t_img *img);
void	*load_img_in_mlx(void *mlx, char *filename);
void	read_map(t_data *data, t_img *img, char *filename);

/* bsf cheack */
bool	can_goal(t_data *data, char **bfs, int x, int y);
void	free_map(char **map, int rows);
// bool	bfs(t_data *data, t_queue *queue, char **map, int s_i, int s_j);
void	init_queue(t_queue *queue, int width, int height);
void	enqueue(t_queue *queue, t_pos *input, int que_max);
t_pos	*dequeue(t_queue *queue, int que_max);
bool	check(t_data *data, char **map, int x_i, int y_j);



int		map_error_cheack(t_data *data, int x, int y, t_img *img);
/* set */
void	disply_img(t_data *data, void *p_img[MAX_MAP][MAX_MAP]);

/* event */
int		key_push(int keycode, t_data *data);
void	move_player_y(t_data *data, t_img *img, int x, int y, int m);
void	move_player_x(t_data *data, t_img *img, int x, int y, int m);
int		window_close(t_data *data);

#endif
