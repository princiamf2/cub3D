/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utis_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:02:45 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 14:50:43 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void sp_rel(const t_game *g, t_spdraw *d)
{
    d->spx = g->enemy.x - g->pl.x;
    d->spy = g->enemy.y - g->pl.y;
}

int sp_cam(const t_game *g, t_spdraw *d)
{
    double det;
    
    det = g->pl.planex * g->pl.diry - g->pl.dirx * g->pl.planey;
    d->invdet = 1.0 / det;
    d->tx = d->invdet * (g->pl.diry * d->spx - g->pl.dirx * d->spy);
    d->ty = d->invdet * (-g->pl.planex * d->spx + g->pl.planey * d->spy);
    return (d->ty <= 0.0001);
}

void sp_project(const t_game *g, t_spdraw *d)
{
    d->h = (int)(g->frame.h / d->ty);
    d->w = (int)(d->h * ((double)g->enemy_s.frame_w / (double)g->enemy_s.row_h));
    d->scrx = (int)((g->frame.w / 2.0) * (1.0 + d->tx / d->ty));
}

void sp_clip(const t_game *g, t_spdraw *d)
{
    int hh;
    int wh;
    int midh;
    
    hh = d->h / 2;
    wh = d->w / 2;
    midh = g->frame.h / 2;
    d->starty = -hh + midh;
    if (d->starty < 0)
        d->starty = 0;
    d->endy = hh + midh;
    if (d->endy >= g->frame.h)
        d->endy = g->frame.h - 1;
    d->startx = -wh + d->scrx;
    if (d->startx < 0)
        d->startx = 0;
    d->endx = wh + d->scrx;
    if ( d->endx >= g->frame.w)
        d->endx = g->frame.w - 1;
}

int collide_circle(t_game *g, double cx, double cy, double r)
{
    if (is_wall(g, cx - r, cy))
        return (1);
    if (is_wall(g, cx + r, cy))
        return (1);
    if (is_wall(g, cx, cy - r))
        return (1);
    if (is_wall(g, cx, cy + r))
        return (1);
    return (0);
}