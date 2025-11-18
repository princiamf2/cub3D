/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:00:00 by michel            #+#    #+#             */
/*   Updated: 2025/11/18 11:59:33 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_BONUS_H
# define SPRITES_BONUS_H

# include "cub3d.h"

# define SPRITE_ROW_FRONT 0
# define SPRITE_ROW_RIGHT 1
# define SPRITE_ROW_BACK  3
# define SPRITE_ROW_LEFT  2
# define SPRITE_RADIUS 0.2

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
#endif
