/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:13:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/12 04:11:39 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* header*/
# include "get_next_line.h"
// # include "ft_printf.h"

/* mlx library */
# include <mlx.h>

/* library */
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

/* define */
# define IMG_SIZE	32

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
	int			fd;
	int			count;
	int			coll_con;
	int			y_column;//列(縦軸)
	int			x_row;//行(横軸)
	void		*p[1000][1000];
	t_player	player;
}				t_data;

#endif
