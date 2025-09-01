/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:28:12 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 13:56:54 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_px(t_img *img, int x, int y, int color)
{
    char *p;
    
    if (x < 0 || x >= img->w || y < 0 || y >= img->h)
        return ;
    p = img->addr + y * img->line_len + x * (img->bpp / 8);
    *(int *)p = color;
}

void draw_column_wall(t_game *game, t_rc *r)
{
    int y;
    int color;
    
    color = 0xB0B0B0;
    if (r->side)
        color = (color >> 1) & 0x7F7F7F;
    y = r->start;
    while (y <= r->end)
    {
        put_px(&game->frame, r->x, y, color);
        y++;
    }
}

int game_render(t_game *game)
{
    int x;
    t_rc r;

    enemy_world_update(game);
    fill_bg(game);
    x = 0;
    while (x < game->frame.w)
    {
        rc_prepare(game, &r, x);
        rc_run_dda(game, &r);
        rc_project(game, &r);
        game->zbuf[r.x] = r.perp;
        draw_column_wall(game, &r);
        x++;
    }
    draw_enemy_3d(game);
    mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
    return (0);
}

