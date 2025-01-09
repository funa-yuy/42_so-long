/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:13:57 by miyuu             #+#    #+#             */
/*   Updated: 2025/01/09 16:37:41 by miyuu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define T_SIZE 32

typedef struct s_point{
	int			x;
	int			y;
	void		*game_img;
}			t_point;

typedef struct s_img{
	// char	**repo;
	// char	**fill;
	// int		empty;//何もないとこの数
	// int		wall;//数
	// int		collects;//数
	// int		exit;//数
	// int		player;//数
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
	int		y_column;//列(縦軸)
	int		x_row;//行(横軸)
	// char	*addr;
	// int		bits_per_pixel;
	// int		line_length;
	// int		endian;
	t_point	p[1000][1000];
	t_point player;
}				t_data;


