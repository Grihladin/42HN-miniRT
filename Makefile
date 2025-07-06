# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 10:03:19 by psenko            #+#    #+#              #
#    Updated: 2025/07/06 01:36:02 by mratke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=miniRT
LIBMLX=MLX42/build/libmlx42.a
HEADER=miniRT.h
GETNEXTLINE=get_next_line/get_next_line.a
LIBFT=libft/libft.a
FTPRINTF=ft_printf/ft_printf.a
GLFW_PATH = $(shell brew --prefix glfw)
CFLAGS=-Wall -Wextra -Werror -Ofast -ffast-math -march=native
CFLAGS += -I$(GLFW_PATH)/include -Ilibft/include -Iget_next_line -Ift_printf
LDFLAGS += -L$(GLFW_PATH)/lib -lglfw
# -g -fsanitize=address
LIBS=$(GETNEXTLINE) $(FTPRINTF) $(LIBFT) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
# CFLAGS_TEST=-Wall -Wextra -Werror -g -fsanitize=address

# Get next line sources and objects
GNL_SOURCES=get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_OBJECTS=$(GNL_SOURCES:.c=.o)

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

# Check if Homebrew is installed
BREW_EXISTS := $(shell command -v brew 2> /dev/null)
GLFW_EXISTS := $(shell brew list glfw 2> /dev/null)
CMAKE_EXISTS := $(shell brew list cmake 2> /dev/null)

all: check-and-install-deps $(NAME)

# Check and install dependencies automatically
check-and-install-deps:
	@echo "🔍 Checking dependencies..."
ifndef BREW_EXISTS
	@echo "❌ Error: Homebrew not found!"
	@echo "📋 Please install Homebrew first: https://brew.sh"
	@echo "💡 Run: /bin/bash -c \"\$$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
	@exit 1
endif
ifndef GLFW_EXISTS
	@echo "📦 Installing GLFW..."
	@brew install glfw
endif
ifndef CMAKE_EXISTS
	@echo "📦 Installing CMake..."
	@brew install cmake
endif
	@echo "✅ All dependencies ready!"

clean:
	rm -rf $(OBJ_DIR)
	make -C libft fclean
	make -C ft_printf fclean
	rm -f $(GNL_OBJECTS) $(GETNEXTLINE)
	rm -rf MLX42/build

fclean: clean
	rm -f $(NAME)
#	make -C MLX42/build clean

re:	fclean all

$(NAME): $(LIBFT) $(FTPRINTF) $(GETNEXTLINE) $(LIBMLX) $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)
	@echo "\033[0;32m🎉 $(NAME) built successfully!\033[0m"

$(LIBFT):
	git submodule update --init --recursive
	make -C libft
	make -C libft bonus

$(FTPRINTF):
	git submodule update --init --recursive
	make -C ft_printf

$(GETNEXTLINE): $(GNL_OBJECTS)
	ar -rs $(GETNEXTLINE) $(GNL_OBJECTS)

# Delete Debug options after
$(LIBMLX):
	git submodule update --init --recursive
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4
# -DDEBUG=1 -DGLFW_FETCH=0

# Rule to compile .c files into the object directory
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Rule to compile get_next_line object files
get_next_line/%.o: get_next_line/%.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re check-and-install-deps
