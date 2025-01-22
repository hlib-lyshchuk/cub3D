# Compiler options.
CC = cc
CFLAGS = -I$(INC_DIR)						\
	 -Wall -Wextra -Wsign-conversion -pedantic -Werror	\
	 -g

# Headers.
INC_DIR = include

# Source files.
SRC_DIR = src
SRC_FILES = main.c							\
		utils/ft_errmsg.c utils/ft_get_map_row.c		\
		utils/ft_mlx_exit.c					\
		parse/ft_parse.c					\
		init/ft_prep_data.c init/ft_free_s_args_content.c	\
		init/ft_free_s_data_content.c

SRC_FILES := $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files.
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Name of the resulting binary file.
NAME = cub3D

# For other Makefiles.
EXTERNAL_DIR = external
MAKE = make

# Libft.
LIBFT_DIR = $(EXTERNAL_DIR)/Libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)/$(LIBFT_NAME)
LIBFT_CLEAN = fclean

# minilibx-linux.
MLX_DIR = $(EXTERNAL_DIR)/minilibx-linux
LIBMLX_A = $(MLX_DIR)/libmlx.a
LIBMLX_LINUX_A = $(MLX_DIR)/libmlx_Linux.a
MLX = $(MLX_DIR)/$(MLX_BUILD_TARGET)
MLX_CLEAN = clean

# Targets.
all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX_A) $(LIBMLX_LINUX_A) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -L$(LIBFT_DIR) -lft	\
		-L$(MLX_DIR) -lmlx -lXext -lX11 -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)			# Create the $(OBJ_DIR) if it doesn't exist.
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_NAME)

$(LIBMLX_A):
	$(MAKE) -C $(MLX_DIR) $(MLX_BUILD_TARGET)

$(LIBMLX_LINUX_A):
	$(MAKE) -C $(MLX_DIR) $(MLX_BUILD_TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_CLEAN)
	$(MAKE) -C $(MLX_DIR) $(MLX_CLEAN)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
