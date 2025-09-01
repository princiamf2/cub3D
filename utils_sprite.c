/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:02:41 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 16:33:05 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long now_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((long)tv.tv_sec * 1000L + (long)tv.tv_usec / 1000L);
}

double dabsval(double v)
{
    if (v < 0.0)
        return (-v);
    else
        return (v);
}

int is_blocking_cell(char c)
{
    return (c == '1' || c == ' ');
}

int is_wall(t_game *g, double x, double y)
{
    int mx;
    int my;

    mx = (int)x;
    my = (int)y;
    if (my < 0 || mx < 0 || my >= g->map.height || mx >= g->map.width)
        return (1);
    return (is_blocking_cell(g->map.grid[my][mx]));
}

int sprite_px(t_sprite *s, int sx, int sy)
{
    int bytepp;
    char *p;
    int offx;
    int offy;
    
    if (sx < 0 || sy < 0 || sx >= s->frame_w || sy >= s->row_h)
        return (SPRITE_CHROMA);
    bytepp = s->bpp / 8;
    offx = s->cur * s->frame_w + sx;
    offy = s->row * s->row_h + sy;
    p = s->addr + offy * s->line_len + offx * bytepp;
    return (*(int *)p);
}

void sp_draw_col(t_game *g, t_spdraw *d, int x)
{
    int y;
    int texx;
    int texy;
    int col;

    texx = ((x - (-d->w / 2 + d->scrx)) * g->enemy_s.frame_w * 256) / (d->w * 256);
    if (!(d->ty > 0.0 && x >= 0 && x < g->frame.w && d->ty < g->zbuf[x]))
        return ;
    y = d->starty;
    while (y <= d->endy)
    {
        texy = ((y - (-d->h / 2 + g->frame.h / 2)) * g->enemy_s.row_h * 256)
                / (d->h * 256);
        col = sprite_px(&g->enemy_s, texx, texy);
        if (col == g->enemy_s.bgcol)
        {
            y++;
            continue;
        }
        if ((col & 0x00FFFFFF) == (SPRITE_CHROMA & 0x00FFFFFF))
        {
            y++;
            continue;
        }
        put_px(&g->frame, x, y, col);
        y++;
    }
}