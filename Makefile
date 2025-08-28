# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpadenko <dpadenko@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/02 20:29:27 by dpadenko          #+#    #+#              #
#    Updated: 2025/08/28 17:31:22 by dpadenko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
CC=cc
CFLAGS=-Werror -Wextra -Wall -MMD -MP
BUILD=build
OBJDIR=$(BUILD)/obj

SRCDIR=src
INCDIR=include

LIBDIR=lib
LIBFT_DIR=$(LIBDIR)/libft
LIBFT=$(LIBFT_DIR)/libft.a

GNL_DIR=$(LIBDIR)/gnl_fdf

MLX_DIR=$(LIBDIR)/minilibx-linux
MLX=$(MLX_DIR)/libmlx.a

SRCS=$(wildcard $(SRCDIR)/*.c)
GNL_SRCS=$(wildcard $(GNL_DIR)/*.c)

OBJS=$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o) \
		$(GNL_SRCS:$(GNL_DIR)/%.c=$(OBJDIR)/gnl_fdf/%.o)

DEPS=$(OBJS:.o=.d)

INCLUDES=-I$(INCDIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

LDFLAGS=-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

.PHONY: clean fclean all re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(MLX):
	$(MAKE) -C $(MLX_DIR) all

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/gnl_fdf/%.o: $(GNL_DIR)/%.c | $(OBJDIR)/gnl_fdf
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/gnl_fdf:
	mkdir -p $(OBJDIR)/gnl_fdf

clean:
	$(RM) -r $(BUILD)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME)
	@if [ -f "$(LIBFT)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi

re: fclean all

-include $(DEPS)