/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:44:38 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 17:37:18 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void rotate(t_game *game, double ang)
{
    double odx;
    double opx;
    
    odx = game->pl.dirx;
    opx = game->pl.planex;
    game->pl.dirx = game->pl.dirx * cos(ang) - game->pl.diry * sin(ang);
    game->pl.diry = odx * sin(ang) + game->pl.diry * cos(ang);
    game->pl.planex = game->pl.planex * cos(ang) - game->pl.planey * sin(ang);
    game->pl.planey = opx * sin(ang) + game->pl.planey * cos(ang);
}

int on_key_press(int key, t_game *game)
{
    if (key == KEY_ESC)
        return (on_destroy(game));
    if (key == KEY_GAUCHE)
        rotate(game, -0.05);
    if (key == KEY_DROITE)
        rotate(game, 0.05);
    if (key == KEY_W) // avancer
{
    if (game->map.grid[(int)(game->pl.y)][(int)(game->pl.x + game->pl.dirx * MOVE_SPEED)] != '1')
        game->pl.x += game->pl.dirx * MOVE_SPEED;
    if (game->map.grid[(int)(game->pl.y + game->pl.diry * MOVE_SPEED)][(int)(game->pl.x)] != '1')
        game->pl.y += game->pl.diry * MOVE_SPEED;
}
if (key == KEY_S) // reculer
{
    if (game->map.grid[(int)(game->pl.y)][(int)(game->pl.x - game->pl.dirx * MOVE_SPEED)] != '1')
        game->pl.x -= game->pl.dirx * MOVE_SPEED;
    if (game->map.grid[(int)(game->pl.y - game->pl.diry * MOVE_SPEED)][(int)(game->pl.x)] != '1')
        game->pl.y -= game->pl.diry * MOVE_SPEED;
}

    return (0);
}

int on_destroy(t_game *game)
{
    game->running = 0;
    mlx_loop_end(game->mlx);
    return (0);
}