/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:08:10 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 17:48:13 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void enemy_world_init(t_game *game, double x, double y)
{
    game->enemy.x = x;
    game->enemy.y = y;
    game->enemy.vx = 1.0;
    game->enemy.vy = 0.0;
    game->enemy.moving = 1;
}

void enemy_pick_row_from_velocity(t_game *g)
{
    double det;
    double invdet;
    double tvx;
    double tvy;

    /* base caméra du joueur */
    det = g->pl.planex * g->pl.diry - g->pl.dirx * g->pl.planey;
    invdet = 1.0 / det;

    /* transformée caméra appliquée au vecteur vitesse (vx, vy) */
    tvx = invdet * (g->pl.diry * g->enemy.vx - g->pl.dirx * g->enemy.vy);
    tvy = invdet * (-g->pl.planex * g->enemy.vx + g->pl.planey * g->enemy.vy);

    sprite_set_row(&g->enemy_s, enemy_row_from_camvel(tvx, tvy));
}

void enemy_world_update(t_game *game)
{
    long    ms;
    double  dt;
    double  step;
    double  nx;
    double  ny;

    ms = now_ms();
    dt = (ms - game->enemy.last_ms) / 1000.0;
    if (dt <= 0.0)
        dt = 0.0;
    if (dt > 0.05)          /* clamp pour éviter gros sauts si lag */
        dt = 0.05;
    game->enemy.last_ms = ms;

    /* vitesse en cases/s -> déplacement par frame = ENEMY_SPEED * dt */
    step = ENEMY_SPEED * dt;
    game->enemy.moving = (step > 0.0);

    /* tentative de mouvement avec collision séparée X/Y et rayon */
    nx = game->enemy.x + game->enemy.vx * step;
    if (!collide_circle(game, nx, game->enemy.y, ENEMY_RADIUS))
        game->enemy.x = nx;
    else
        game->enemy.vx = -game->enemy.vx; /* rebond simple */

    ny = game->enemy.y + game->enemy.vy * step;
    if (!collide_circle(game, game->enemy.x, ny, ENEMY_RADIUS))
        game->enemy.y = ny;
    else
        game->enemy.vy = -game->enemy.vy;

    /* si “coincé” (mur tout proche), pivote un peu la direction */
    if (collide_circle(game,
            game->enemy.x + game->enemy.vx * 0.1,
            game->enemy.y + game->enemy.vy * 0.1, ENEMY_RADIUS))
    {
        double tmp = game->enemy.vx;
        game->enemy.vx = -game->enemy.vy;
        game->enemy.vy = tmp;
    }

    enemy_pick_row_from_velocity(game);
    sprite_step(&game->enemy_s, SPRITE_MS_FRAME, game->enemy.moving);
}

void sp_draw_span(t_game *g, t_spdraw *d)
{
    int x;
    
    x = d->startx;
    while (x <= d->endx)
    {
        sp_draw_col(g, d, x);
        x++;
    }
}

void draw_enemy_3d(t_game *g)
{
    t_spdraw d;
    
    sp_rel(g, &d);
    if (sp_cam(g, &d))
        return ;
    sp_project(g, &d);
    sp_clip(g, &d);
    sp_draw_span(g, &d);
}