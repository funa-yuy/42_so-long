# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 01:21:55 by miyuu             #+#    #+#              #
#    Updated: 2025/01/12 04:11:35 by miyuu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# cc -Wall -Wextra -Werror -fsanitize=address -g -Iminilibx-linux -Ilib/get_next_line/ main.c -Lminilibx-linux -lmlx -lXext -lX11  lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = so_long

# Directories
SRC_DIR = ./src
LIBFT_DIR = ./lib//libft
PRINTF_DIR = ./lib/ft_printf
GNL_DIR = ./lib/get_next_line
MLX_DIR	= ./minilibx-linux
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11

# Source files
SRC_FILES = main.c \
			move.c \
			read_img.c \
			read_map.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
		$(addprefix $(GNL_DIR)/, $(GNL_FILES))

# Object files
OBJS = $(SRC:.c=.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT) $(PRINTF) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
