# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpadenko <dpadenko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 20:29:27 by dpadenko          #+#    #+#              #
#    Updated: 2024/02/03 14:32:45 by dpadenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
CC=cc
FLAGS=-Werror -Wextra -Wall

SRC= draw.c \
		draw_utils.c \
		main.c \
		keys.c \
		colors.c \
		init_window.c \
		init_window_utils.c \
		get_next_line.c \
		get_next_line_utils.c

MLX_NAME = mlx
MLX = $(MLX_PATH)$(MLX_NAME)

LIBDIR=./libft
LIBFT=$(LIBDIR)/libft.a
OBJ=$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< -I.

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) -L$(LIBDIR) -lft -lXext -lX11 -l$(MLX_NAME) -lm -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBDIR) all

.PHONY: clean fclean all re

clean:
	$(MAKE) -C $(LIBDIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBDIR) fclean
	rm -f $(NAME)

re: fclean all