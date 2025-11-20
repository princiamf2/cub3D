/* ************************************************************************** */
/*                                                                            */
/*                            :::      ::::::::   */
/*   cub3d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel & nico                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:00:00 by fusion            #+#    #+#             */
/*   Updated: 2025/10/30 16:00:00 by fusion           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <limits.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h>


# define SCREEN_W  1024
# define SCREEN_H  768

# define TEX_N 0
# define TEX_S 1
# define TEX_W 2
# define TEX_E 3
# define TEX_DOOR 4
# define TEX_COUNT 5

#define BIG 1e30

# define SPRITE_XPM_PATH "./textures/test.xpm"
# define SPRITE_SCALE 0.6
# define DOOR_SCALE 1.0
# define MAX_SPRITES 128
# define MAX_DOOR 124
# define DOOR_FRAMES 7

typedef struct s_tex {
	void	*img;
	int		*data;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
	int		frame_w;
	int		frame_h;
	int		frames;
}	t_tex;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player {
	double	x;
	double	y;
	double	dir;		// angle en rad
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_sprite {
	double	x;
	double	y;
	double	dist;
	int		anim_frame;
	int		type;
}	t_sprite;

typedef struct	s_door
{
	int y;
	int x;
	int open;
	int	frame;
	int anim_dir;
	double timer;
}	t_door;

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*frame;
	int		*frame_data;
	int		scr_w;
	int		scr_h;

	/* textures */
	char	*tex_path[TEX_COUNT];
	t_tex	tex[TEX_COUNT];
	t_tex	sprite_tex;

	/* colors */
	int		floor_color;
	int		ceil_color;

	/* map & player */
	t_map	map;
	t_player player;

	/* sprites (bonus) */
	t_sprite sprites[MAX_SPRITES];
	t_door	 doors[MAX_DOOR];
	int		 door_count;
	int		sprite_count;

	/* zbuffer */
	double	*zbuffer;

	/* input state */
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_l;
	int		key_r;

	int		sprite_anim_tick;

}	t_game;

/* main pipeline */
int		parse_cub(t_game *g, const char *path);
int		game_init_mlx(t_game *g);
void	game_init_defaults(t_game *g);
void	game_destroy(t_game *g);
void	game_loop(t_game *g);

/* render */
void	render_frame(t_game *g);

/* input */
int		key_press(int keycode, t_game *g);
int		key_release(int keycode, t_game *g);
int		close_win(t_game *g);
void	handle_input(t_game *g);

/* utils */
int		err(const char *msg);
char	*ft_strdup(const char *s);
char	**split_lines_from_fd(int fd, int *out_count);
void	free_lines(char **lines);
char	*ft_strtrim_spaces(char *s);
int		ft_atoi_strict(const char *s, int *ok);
#endif
