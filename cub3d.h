/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:39:29 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 17:35:56 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <sys/time.h>

# define WIN_W 1024
# define WIN_H 640

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_SP 4

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_HAUT 65362
# define KEY_S 115
# define KEY_BAS 65364
# define KEY_A 97
# define KEY_GAUCHE 65361
# define KEY_D 100
# define KEY_DROITE 65363
# define KEY_SPACE 32
# define MOVE_SPEED 0.05
# define ENEMY_SPEED 0.8
# define ENEMY_RADIUS 0.10
# define SPRITE_CHROMA 0x00FF00FF
# define SPRITE_MS_FRAME 120

#ifndef OPEN_MAX
#define OPEN_MAX 1024
#endif

typedef struct s_rgb
{
    int r;
    int g;
    int b;
    int packed;
}t_rgb;

typedef struct s_tex
{
    void *img;
    char *addr;
    int w;
    int h;
    int bpp;
    int line_len;
    int endian;
    char *path;
} t_tex;

typedef struct s_map
{
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_player
{
    double x;
    double y;
    double dirx;
    double diry;
    double planex;
    double planey;
} t_player;

typedef struct s_cfg
{
    char *no;
    char *so;
    char *we;
    char *ea;
    t_rgb floor;
    t_rgb ceil;
    int have_player;
    int have_enemy;
    int enemy_count;
    char spawn_dir;
    int spawn_x;
    int spawn_y;
} t_cfg;

typedef struct s_img
{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int w;
    int h;
} t_img;

typedef struct s_rc
{
    int x;
    int mapx;
    int mapy;
    int stepx;
    int stepy;
    int side;
    int start;
    int end;
    double camx;
    double rayx;
    double rayy;
    double dx;
    double dy;
    double sx;
    double sy;
    double perp;
    double lineh;
} t_rc;

typedef struct s_sprite
{
    void *img;
    char *addr;
    int bpp;
    int w;
    int h;
    int rows_total;
    int row;
    int row_h;
    int frames_total;
    int frame_w;
    int endian;
    int line_len;
    int cur;
    long last_ms;
    int bgcol;
} t_sprite;

typedef struct s_actor
{
    double x;
    double y;
    double vx;
    double vy;
    int moving;
    long last_ms;
} t_actor;

typedef struct s_spdraw
{
    double spx;
    double spy;
    double invdet;
    double tx;
    double ty;
    int scrx;
    int h;
    int w;
    int startx;
    int starty;
    int endx;
    int endy;
} t_spdraw;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img frame;
    t_player pl;
    t_map map;
    t_tex ex[4];
    t_cfg cfg;
    int running;
    double *zbuf;
    t_sprite enemy_s;
    t_actor enemy;
} t_game;

int err(char *msg);
void *xfree(void *p);
int ft_isspace(char c);
void set_player_from_spawn(t_game *g);
int game_init_mlx(t_game *game);
int load_texture(t_game *game);
void game_init_defaults(t_game *game);
char *read_all(char *path);
char **split_lines_keep(char *buf, int *n);
char *trim_inplace(char *s);
int pack_rgb(int r, int g, int b);
int is_mapline(char *s);
int is_wall_or_space(char c);
int parse_map_block(t_game *game, char **lines, int i, int n);
int copy_map(t_game *g, char **lines, int i, int h, int w);
void measure_map(char **lines, int i, int n, int *h, int *w);
int validate_map_closed(t_map *m);
void free_split(char **v);
int parse_rgb(char *s, t_rgb *out);
int parse_kv_line(t_game *game, char *line);
int on_destroy(t_game *game);
int parse_cub(t_game *game, char *path);
void game_destroy(t_game *game);
int on_key_press(int key, t_game *game);
int game_render(t_game *game);
void put_px(t_img *img, int x, int y, int color);
void fill_bg(t_game *game);
void rc_prepare(t_game *game, t_rc *r, int x);
void rc_run_dda(t_game *game, t_rc *r);
void rc_project(t_game *game, t_rc *r);
void draw_column_wall(t_game *game, t_rc *r);
long now_ms();
double dabsval(double v);
int is_wall(t_game *g, double x, double y);
void sprite_set_row(t_sprite *s, int row);
void sprite_step(t_sprite *s, int ms_per_frame, int is_moving);
void put_px(t_img *img, int x, int y, int color);
void sp_rel(const t_game *g, t_spdraw *d);
int sp_cam(const t_game *g, t_spdraw *d);
void sp_project(const t_game *g, t_spdraw *d);
void sp_clip(const t_game *g, t_spdraw *d);
void sp_draw_col(t_game *g, t_spdraw *d, int x);
int load_sprite(t_game *g, t_sprite *s, const char *path, int frames, int rows);
void enemy_world_init(t_game *game, double x, double y);
void enemy_world_update(t_game *game);
void draw_enemy_3d(t_game *g);
int collide_circle(t_game *g, double cx, double cy, double r);
int enemy_row_from_camvel(double tvx, double tvy);

#endif
