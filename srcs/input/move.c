/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 02:24:33 by michel            #+#    #+#             */
/*   Updated: 2025/11/20 02:24:54 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static int is_wall(t_game *game, double y, double x)
{
    int mx;
    int my;

    mx = (int)x;
    my = (int)y;
	if (my < 0 || my >= game->map.height || mx < 0 || mx >= game->map.width)
        return (1);
	if (game->map.grid[my][mx] == '1')
		return (1);
	if (is_doors_ceil_closed(game, my, mx))
		return (1);
    return (0);
}

static void	update_camera_plane(t_game *g)
{
	g->player.plane_x = -sin(g->player.dir) * 0.66;
	g->player.plane_y = cos(g->player.dir) * 0.66;
}

void	handle_input(t_game *g)
{
	double	m;
	double	r;
	double	nx;
	double	ny;
	double	step;
	double	side;

	m = 0.08;
	r = 0.045;
	/* avant/arrière */
	if (g->key_w || g->key_s)
	{
		step = (g->key_w ? m : -m);
		nx = g->player.x + cos(g->player.dir) * step;
		ny = g->player.y + sin(g->player.dir) * step;
		if (!is_wall(g, g->player.y, nx))
			g->player.x = nx;
		if (!is_wall(g, ny, g->player.x))
			g->player.y = ny;
	}
	/* strafe gauche/droite (A/D) */
	if (g->key_a || g->key_d)
	{
		side = (g->key_d ? 1.0 : -1.0);
		/* plane a une norme ~0.66, on compense pour rester à vitesse ~m */
		nx = g->player.x + g->player.plane_x * (m / 0.66) * side;
		ny = g->player.y + g->player.plane_y * (m / 0.66) * side;
		if (!is_wall(g, g->player.y, nx))
			g->player.x = nx;
		if (!is_wall(g, ny, g->player.x))
			g->player.y = ny;
	}
	/* rotation */
	if (g->key_l)
		g->player.dir -= r;
	if (g->key_r)
		g->player.dir += r;
	/* normalisation de l’angle dans [0, 2π) */
	while (g->player.dir < 0.0)
		g->player.dir += 2.0 * M_PI;
	while (g->player.dir >= 2.0 * M_PI)
		g->player.dir -= 2.0 * M_PI;
	update_camera_plane(g);
}