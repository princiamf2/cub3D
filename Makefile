NAME        = cub3d
NAME_BONUS  = cub3d_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCS        = -Iincludes -Ilibft -Imlx

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = mlx
MLX         = $(MLX_DIR)/libmlx.a

MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR     = srcs
OBJ_DIR     = obj

# ========= MANDATORY =========

SRCS        = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/game_init.c \
	$(SRC_DIR)/game_destroy.c \
	$(SRC_DIR)/game_loop.c \
	$(SRC_DIR)/mlx_init.c \
	$(SRC_DIR)/input/hooks.c \
	$(SRC_DIR)/input/move.c \
	$(SRC_DIR)/render/render_frame.c \
	$(SRC_DIR)/render/raycast.c \
	$(SRC_DIR)/render/raycast_texture.c \
	$(SRC_DIR)/parse/parse.c \
	$(SRC_DIR)/parse/parse_element.c \
	$(SRC_DIR)/parse/parse_color.c \
	$(SRC_DIR)/parse/parse_map.c \
	$(SRC_DIR)/parse/map_check.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/read_file.c

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ========= BONUS =========

SRCS_BONUS  = \
	$(SRC_DIR)/bonus/main_bonus.c \
	$(SRC_DIR)/game_init.c \
	$(SRC_DIR)/game_destroy.c \
	$(SRC_DIR)/mlx_init.c \
	$(SRC_DIR)/input/hooks.c \
	$(SRC_DIR)/input/move.c \
	$(SRC_DIR)/render/raycast.c \
	$(SRC_DIR)/parse/parse_element.c \
	$(SRC_DIR)/parse/parse_color.c \
	$(SRC_DIR)/parse/parse_map.c \
	$(SRC_DIR)/parse/map_check.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/read_file.c \
	$(SRC_DIR)/bonus/parse_cub_bonus.c \
	$(SRC_DIR)/bonus/sprite_bonus.c \
	$(SRC_DIR)/bonus/sprite_ai_bonus.c \
	$(SRC_DIR)/bonus/sprite_draw_bonus.c \
	$(SRC_DIR)/bonus/sprite_update_bonus.c \
	$(SRC_DIR)/bonus/game_loop_bonus.c \
	$(SRC_DIR)/bonus/render_frame_bonus.c \
	$(SRC_DIR)/bonus/doors_bonus.c \
	$(SRC_DIR)/bonus/raycast_texture_bonus.c \
	$(SRC_DIR)/bonus/raycast_door_bonus.c

OBJS_BONUS  = $(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# map utilisée pour `make leaks` (mandatory)
LEAKS_MAP   = maps/test.cub

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)

# règle générique : obj/xxx.o à partir de srcs/xxx.c (gère aussi les sous-dossiers)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean || true
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(LEAKS_MAP)

.PHONY: all clean fclean re leaks bonus
