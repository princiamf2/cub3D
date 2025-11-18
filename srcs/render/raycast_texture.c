/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:19:03 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 15:40:23 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/render.h"

static t_tex    *select_tex(t_game *game, t_ray *r)
{
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

    put_ceil_floor(g, x, r->draw_start, 0, g->ceil_color);
    tex = select_tex(g, r);
    r->tex_x = (int)(r->wall_x * (double)tex->w);
    if (r->side == 0 && r->ray_dir_x > 0.0)
        r->tex_x = tex->w - r->tex_x - 1;
    if (r->side == 1 && r->ray_dir_y < 0.0)
        r->tex_x = tex->w - r->tex_x - 1;
    step = 1.0 * tex->h / (double)r->line_h;
    tex_pos = (r->draw_start - (double)g->scr_h / 2 + (double)r->line_h / 2) * step;
    y = r->draw_start;
    while (y <= r->draw_end)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->h)
            tex_y = tex->h - 1;
        tex_pos += step;
        color = tex->data[tex->w * tex_y + r->tex_x];
        g->frame_data[y * g->scr_w + x] = color;
        y++;
    }
    put_ceil_floor(g, x, g->scr_h, r->draw_end + 1, g->floor_color);
}