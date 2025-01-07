# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 01:21:55 by miyuu             #+#    #+#              #
#    Updated: 2025/01/08 01:58:36 by miyuu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long

# Directories
SRC_DIR = ./src
LIBFT_DIR = ./lib//libft
GNL_DIR = ./lib/get_next_line
MLX_DIR	= ./minilibx-linux
MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11

# Source files
SRC_FILES = create_stack.c \
			error_check.c \
			free_stack.c \
			ft_stacksize.c \
			marge_move.c \
			merge_operations.c \
			merge_diff.c \
			ps_atoi.c \
			push_swap.c \
			merge_sort.c \
			sort_push.c \
			sort_reverse_rotate.c \
			sort_rotate.c \
			sort_short_utils.c \
			sort_short.c \
			sort_swap.c

GNL_FILES = get_next_line.c \
			get_next_line_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
		$(addprefix $(GNL_DIR)/, $(GNL_FILES))

# Object files
OBJS = $(SRC:.c=.o)


# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(GNL_FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) $(GNL_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
