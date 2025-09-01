/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:16:24 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 17:50:02 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void fill_bg(t_game *game)
{
    int x;
    int y;
    
    y = 0;
    while (y < game->frame.h / 2)
    {
        x = 0;
        while (x < game->frame.w)
        {
            put_px(&game->frame, x, y, game->cfg.ceil.packed);
            x++;
        }
        y++;
    }
    while (y < game->frame.h)
    {
        x = 0;
        while (x < game->frame.w)
        {
            put_px(&game->frame, x, y, game->cfg.floor.packed);
            x++;
        }
        y++;
    }
}

void rc_prepare(t_game *game, t_rc *r, int x)
{
    double invx;
    double invy;
    
    r->x = x;
    r->camx = 2.0 * x / (double)game->frame.w - 1.0;
    r->rayx = game->pl.dirx + game->pl.planex * r->camx;
    r->rayy = game->pl.diry + game->pl.planey * r->camx;
    r->mapx = (int)game->pl.x;
    r->mapy = (int)game->pl.y;
    if (r->rayx == 0.0)
        r->dx = 1e30;
    else
    {
        invx = 1.0 / r->rayx;
        if (invx < 0.0)
            r->dx = -invx;
        else
            r->dx = invx;
    }
    if (r->rayy == 0.0)
        r->dy = 1e30;
    else
    {
        invy = 1.0 / r->rayy;
        if (invy < 0.0)
            r->dy = -invy;
        else
            r->dy = invy; 
    }
    if (r->rayx < 0.0)
    {
        r->stepx = -1;
        r->sx = (game->pl.x - r->mapx) * r->dx;
    }
    else
    {
        r->stepx = 1;
        r->sx = (r->mapx + 1.0 - game->pl.x) * r->dx;
    }
    if (r->rayy < 0.0)
	{
		r->stepy = -1;
		r->sy = (game->pl.y - r->mapy) * r->dy;
	}
    else
	{
		r->stepy = 1;
		r->sy = (r->mapy + 1.0 - game->pl.y) * r->dy;
	}
}

void rc_run_dda(t_game *game, t_rc *r)
{
    while (game->map.grid[r->mapy][r->mapx] != '1')
    {
        if (r->sx < r->sy)
        {
            r->sx += r->dx;
            r->mapx += r->stepx;
            r->side = 0;
        }
        else
        {
            r->sy += r->dy;
            r->mapy += r->stepy;
            r->side = 1;
        }
    }
}

void rc_project(t_game *game, t_rc *r)
{
    if (r->side == 0)
        r->perp = (r->mapx - game->pl.x + (1 - r->stepx) / 2.0) / r->rayx;
    else
        r->perp = (r->mapy - game->pl.y + (1 - r->stepy) / 2.0) / r->rayy;
    if (r->perp < 1e-6)
        r->perp = 1e-6;
    r->lineh = game->frame.h / r->perp;
    r->start = (int)(-r->lineh / 2.0 + game->frame.h / 2.0);
    r->end = (int)(r->lineh / 2.0 + game->frame.h / 2.0);
    if (r->start < 0)
        r->start = 0;
    if (r->end >= game->frame.h)
        r->end = game->frame.h - 1;
}