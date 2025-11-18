/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:05:55 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 21:02:42 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void game_init_defaults(t_game *g)
{
    int i;

    g->mlx = NULL;
    g->win = NULL;
    g->frame = NULL;
    g->frame_data = NULL;
    g->scr_w = SCREEN_W;
    g->scr_h = SCREEN_H;
    i = 0;
    while (i < TEX_COUNT)
    {
        g->tex_path[i] = NULL;
        g->tex[i].img = NULL;
        i++;
    }
    g->sprite_tex.img = NULL;
	g->sprite_tex.data = NULL;
	g->sprite_tex.w = 0;
	g->sprite_tex.h = 0;
	g->sprite_tex.bpp = 0;
	g->sprite_tex.line_len = 0;
	g->sprite_tex.endian = 0;
    g->sprite_tex.frame_w = 0;
    g->sprite_tex.frame_h = 0;
    g->sprite_tex.frames = 0;
    g->floor_color = -1;
    g->ceil_color = -1;
    g->map.grid = NULL;
    g->map.width = 0;
    g->map.height = 0;
    g->player.x = -1;
    g->player.y = -1;
    g->player.dir = 0;
    g->player.plane_x = 0;
    g->player.plane_y = 0;
    g->sprite_count = 0;
    g->sprite_anim_tick = 0;
    g->zbuffer = NULL;
    g->key_w = 0;
    g->key_s = 0;
    g->key_a = 0;
    g->key_d = 0;
    g->key_r = 0;
    g->key_l = 0;
    g->sprite_count = 0;
}