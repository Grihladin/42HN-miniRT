# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 10:03:19 by psenko            #+#    #+#              #
#    Updated: 2025/07/06 10:36:44 by mratke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=miniRT
LIBMLX=MLX42/build/libmlx42.a
HEADER=inc/miniRT.h
GETNEXTLINE=get_next_line/get_next_line.a
LIBFT=libft/libft.a
FTPRINTF=ft_printf/ft_printf.a
GLFW_PATH = $(shell brew --prefix glfw)
CFLAGS=-Wall -Wextra -Werror -O3 -ffast-math -march=native -fno-finite-math-only
CFLAGS += -I$(GLFW_PATH)/include -Ilibft/inc -Iget_next_line/inc -Ift_printf/inc -Iinc
LDFLAGS += -L$(GLFW_PATH)/lib -lglfw
# -g -fsanitize=address
LIBS=$(GETNEXTLINE) $(FTPRINTF) $(LIBFT) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
# CFLAGS_TEST=-Wall -Wextra -Werror -g -fsanitize=address

# Get next line sources and objects
GNL_SOURCES=get_next_line/src/get_next_line.c get_next_line/src/get_next_line_utils.c
GNL_OBJECTS=$(GNL_SOURCES:.c=.o)

SOURCES=src/miniRT.c \
	src/hooks/hooks.c \
	src/hooks/mouse_hooks.c \
	src/utils/utils1.c \
	src/utils/errors.c \
	src/utils/rt_split.c \
	src/utils/ft_atof.c \
	src/utils/frees.c \
	src/utils/check_unique_element.c \
	src/utils/framebuffer.c \
	src/parsing/read_parameters.c \
	src/parsing/read_elements.c \
	src/parsing/read_elements1.c \
	src/parsing/read_elements2.c \
	src/parsing/add_element.c \
	src/parsing/read_sphere.c \
	src/drawing/redraw.c \
	src/moving/zoom.c \
	src/moving/rotate.c \
	src/moving/move.c \
	src/vector_operations/vector_colors.c \
	src/vector_operations/vector_operations1.c \
	src/vector_operations/vector_operations2.c \
	src/vector_operations/vector_operations3.c \
	src/raytracing/sphere.c \
	src/raytracing/cylinder.c \
	src/raytracing/plane.c \
	src/raytracing/shadow.c \
	src/raytracing/lightning.c \
	src/raytracing/cylinder_body.c \
	src/raytracing/cylinder_cap.c


OBJ_DIR=obj

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
	@echo "🔄 Initializing git submodules..."
	@git submodule update --init --recursive
	@echo "🔍 Verifying submodules are properly initialized..."
	@if [ ! -f "libft/Makefile" ]; then \
		echo "⚠️  libft not properly initialized, retrying..."; \
		git submodule update --init libft; \
	fi
	@if [ ! -f "ft_printf/Makefile" ]; then \
		echo "⚠️  ft_printf not properly initialized, retrying..."; \
		git submodule update --init ft_printf; \
	fi
	@if [ ! -f "get_next_line/src/get_next_line.c" ]; then \
		echo "⚠️  get_next_line not properly initialized, retrying..."; \
		git submodule update --init get_next_line; \
	fi
	@if [ ! -d "MLX42/src" ]; then \
		echo "⚠️  MLX42 not properly initialized, retrying..."; \
		git submodule update --init MLX42; \
	fi
	@echo "✅ All dependencies ready!"

clean:
	rm -rf $(OBJ_DIR)
	@if [ -f libft/Makefile ]; then make -C libft fclean; fi
	@if [ -f ft_printf/Makefile ]; then make -C ft_printf fclean; fi
	rm -f $(GNL_OBJECTS) $(GETNEXTLINE)
	rm -rf MLX42/build

fclean: clean
	rm -f $(NAME)
#	make -C MLX42/build clean

re:	fclean all

$(NAME): $(LIBFT) $(FTPRINTF) $(GETNEXTLINE) $(LIBMLX) $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)
	@echo "\033[0;32m🎉 $(NAME) built successfully!\033[0m"

$(LIBFT): check-and-install-deps
	@if [ -f libft/Makefile ]; then make -C libft; fi
	@if [ -f libft/Makefile ]; then make -C libft bonus; fi

$(FTPRINTF): check-and-install-deps
	@if [ -f ft_printf/Makefile ]; then make -C ft_printf; fi

$(GETNEXTLINE): check-and-install-deps $(GNL_OBJECTS)
	ar -rs $(GETNEXTLINE) $(GNL_OBJECTS)

# Delete Debug options after
$(LIBMLX): check-and-install-deps
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4
# -DDEBUG=1 -DGLFW_FETCH=0

# Rule to compile .c files into the object directory
$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

# Rule to compile get_next_line object files
get_next_line/src/%.o: get_next_line/src/%.c get_next_line/inc/get_next_line.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re check-and-install-deps
