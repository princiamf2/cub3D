# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: michel <michel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:34:36 by mm-furi           #+#    #+#              #
#    Updated: 2025/09/01 13:23:04 by michel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -Imlx
LIBFT = libft/libft.a
SRC = cleanup.c \
	main.c \
	error.c \
	init.c \
	input.c \
	parse_map.c \
	parse_map2.c \
	parser_kv.c \
	parser_rgb.c \
	parser.c \
	render.c \
	utils_render.c \
	utils.c \
	utils_sprite.c \
	utis_draw.c \
	sprite_world.c \
	sprite_spritesheet.c \
	
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
MLXFLAGS = -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

# Compilation des fichiers .c vers obj/*.o
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Création du dossier obj si nécessaire
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

debug: $(OBJ)
	$(CC) $(CFLAGS) -fsanitize=address -g $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
