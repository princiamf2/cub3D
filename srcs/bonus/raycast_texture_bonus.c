/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:19:03 by michel            #+#    #+#             */
/*   Updated: 2025/11/18 19:28:22 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static int  is_door_cell(t_game *g, int my, int mx)
{
    int i;
    
    i = 0;
    while (i < g->door_count)
    {
        if (g->doors[i].x == mx && g->doors[i].y == my)
            return (1);
        i++;
    }
    return (0);
}
static t_tex    *select_tex(t_game *game, t_ray *r)
{
    if (is_door_cell(game, r->map_y, r->map_x))
        return (&game->tex[TEX_DOOR]);
    if (r->side == 0)
    {
        if (r->ray_dir_x > 0.0)
            return (&game->tex[TEX_W]);
        return (&game->tex[TEX_E]);
    }
    if (r->ray_dir_y > 0.0)
        return (&game->tex[TEX_N]);
    return (&game->tex[TEX_S]);
}

static void put_ceil_floor(t_game *game, int x, int to, int from, int color)
{
    int y;

    y = from;
    while (y < to)
    {
        game->frame_data[y * game->scr_w + x] = color;
        y++;
    }
}

void    draw_wall_stripe(t_game *g, int x, t_ray *r)
{
    t_tex   *tex;
    double  step;
    double  tex_pos;
    int     y;
    int     tex_y;
    int     color;
    int     frame_h;
    int     inner_h;

    put_ceil_floor(g, x, r->draw_start, 0, g->ceil_color);
    tex = select_tex(g, r);
    r->tex_x = compute_tex_x(g, r, tex);
    if (tex == &g->tex[TEX_DOOR])
    {
        frame_h = tex->frame_h;
        inner_h = frame_h - (DOOR_INNER_TOP + DOOR_INNER_BOTTOM);
        step = (double)inner_h / (double)r->line_h;
    }
    else
        step = (double)tex->h / (double)r->line_h;
    tex_pos = (r->draw_start - (double)g->scr_h / 2
            + (double)r->line_h / 2) * step;
    y = r->draw_start;
    while (y <= r->draw_end)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex == &g->tex[TEX_DOOR])
        {
            frame_h = tex->frame_h;
            inner_h = frame_h - (DOOR_INNER_TOP + DOOR_INNER_BOTTOM);
            if (tex_y >= inner_h)
                tex_y = inner_h - 1;
            /* 2ᵉ ligne + offset vertical interne */
            tex_y += frame_h + DOOR_INNER_TOP;
        }
        else
        {
            if (tex_y >= tex->h)
                tex_y = tex->h - 1;
        }
        color = tex->data[tex->w * tex_y + r->tex_x];
        g->frame_data[y * g->scr_w + x] = color;
        tex_pos += step;
        y++;
    }
    put_ceil_floor(g, x, g->scr_h, r->draw_end + 1, g->floor_color);
}
