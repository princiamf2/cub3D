/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:00:00 by michel            #+#    #+#             */
/*   Updated: 2025/11/21 03:11:30 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_BONUS_H
# define SPRITES_BONUS_H

# include "cub3d.h"
# include "render.h"

# define SPRITE_ROW_FRONT 0
# define SPRITE_ROW_RIGHT 1
# define SPRITE_ROW_BACK  3
# define SPRITE_ROW_LEFT  2
# define SPRITE_RADIUS 0.2

# define DOOR_FRAMES      7
# define DOOR_INNER_MIN   7
# define DOOR_INNER_W     53
# define DOOR_INNER_TOP    10
# define DOOR_INNER_BOTTOM 8

# define MM_TILE    8
# define MM_RADIUS  6
# define MM_OFFSET_X 10
# define MM_OFFSET_Y 10

typedef struct  s_sprite_proj
{
    double  sprite_x;
    double  sprite_y;
    double  transform_x;
    double  transform_y;
    int     screen_x;
    int     height;
    int     width;
    int     draw_start_y;
    int     draw_end_y;
    int     draw_start_x;
    int     draw_end_x;
}   t_sprite_proj;

void	init_sprites_from_map(t_game *g);
void    render_frame_bonus(t_game *g);
int     parse_cub_bonus(t_game *g, const char *path);
void    update_sprites_from_player(t_game *g);
void    draw_sprites(t_game *g);
void    game_loop_bonus(t_game *g);
void	update_sprites_ai(t_game *g);
void    init_doors_from_map(t_game *g);
int     is_doors_ceil_closed(t_game *g, int my, int mx);
void    try_use_door(t_game *g);
void    update_doors_anim(t_game *g);
t_door  *get_door_of_cell(t_game *g, int mx, int my);
int     compute_door_tex_x(t_game *g, t_ray *r, t_tex *tex);
int     compute_normal_tex_x(t_tex *tex, t_ray *r);
int     compute_tex_x(t_game *g, t_ray *r, t_tex *tex);
int     check_map_closed_bonus(t_map *map, t_player *p);
void    draw_minimap_bonus(t_game *g);
void	mm_draw_sprites(t_game *g);
void	mm_put_pixel(t_game *g, int x, int y, int color);
#endif
