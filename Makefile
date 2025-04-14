# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 10:03:19 by psenko            #+#    #+#              #
#    Updated: 2025/04/14 14:09:29 by psenko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=miniRT
LIBMLX=MLX42/build/libmlx42.a
HEADER=miniRT.h
GETNEXTLINE=get_next_line/get_next_line.a
LIBFT=libft/libft.a
CFLAGS=-Wall -Wextra -Werror -Ofast -ffast-math -flto -march=native
# -g -fsanitize=address
LIBS=-ldl -lglfw -pthread -lm $(LIBFT) $(GETNEXTLINE) MLX42/build/libmlx42.a
# CFLAGS_TEST=-Wall -Wextra -Werror -g -fsanitize=address

SOURCES=miniRT.c info.c read_parameters.c hooks.c read_elements.c \
	rt_split.c

OBJECTS=$(SOURCES:.c=.o)

all: $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	make -C libft fclean
	make -C getnextline fclean
#	make -C MLX42/build clean
	rm -rf MLX42/build/*
	rm -f $(OBJECTS)

re:	fclean all

$(NAME): $(LIBFT) $(GETNEXTLINE) $(LIBMLX) $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o $(NAME)

$(LIBFT):
	make -C libft

$(GETNEXTLINE):
	make -C get_next_line

# Delete Debug options after
$(LIBMLX):
	git submodule update --init --recursive
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4
# -DDEBUG=1 -DGLFW_FETCH=0

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re
