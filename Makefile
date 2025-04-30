# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 10:03:19 by psenko            #+#    #+#              #
#    Updated: 2025/04/30 15:13:01 by psenko           ###   ########.fr        #
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
LIBS=$(LIBFT) $(GETNEXTLINE) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
# CFLAGS_TEST=-Wall -Wextra -Werror -g -fsanitize=address

SOURCES=miniRT.c \
	hooks/hooks.c \
	hooks/mouse_hooks.c \
	utils/utils1.c \
	utils/errors.c \
	utils/rt_split.c \
	utils/ft_atof.c \
	utils/frees.c \
	utils/check_unique_element.c \
	utils/framebuffer.c \
	parsing/read_parameters.c \
	parsing/read_elements.c \
	parsing/read_elements1.c \
	parsing/read_elements2.c \
	parsing/add_element.c \
	parsing/read_sphere.c \
	drawing/redraw.c \
	moving/zoom.c \
	moving/rotate.c \
	moving/move.c \
	vector_operations/vector_colors.c \
	vector_operations/vector_operations1.c \
	vector_operations/vector_operations2.c \
	vector_operations/vector_operations3.c \
	raytracing/sphere.c \
	raytracing/cylinder.c \
	raytracing/plane.c \
	raytracing/shadow.c \
	raytracing/lightning.c \
	raytracing/cylinder_body.c \
	raytracing/cylinder_cap.c


OBJ_DIR=objects

# Prepend the object directory path to each object file, maintaining structure
OBJECTS=$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C libft fclean
	make -C get_next_line fclean
	rm -rf MLX42/build

fclean: clean
	rm -f $(NAME)
#	make -C MLX42/build clean

re:	fclean all

$(NAME): $(LIBFT) $(GETNEXTLINE) $(LIBMLX) $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

$(LIBFT):
	make -C libft

$(GETNEXTLINE):
	make -C get_next_line

# Delete Debug options after
$(LIBMLX):
	git submodule update --init --recursive
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4
# -DDEBUG=1 -DGLFW_FETCH=0

# Rule to compile .c files into the object directory
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re
