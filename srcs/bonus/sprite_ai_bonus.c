/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ai_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18  */
/*   Updated: 2025/11/18  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static int	cell_blocked(t_game *g, int my, int mx)
{
	if (my < 0 || my >= g->map.height || mx < 0 || mx >= g->map.width)
		return (1);
	return (g->map.grid[my][mx] == '1');
}

static int	sprite_collides(t_game *g, double y, double x)
{
	double	r;

	r = SPRITE_RADIUS;
	if (cell_blocked(g, (int)(y - r), (int)(x - r)))
		return (1);
	if (cell_blocked(g, (int)(y - r), (int)(x + r)))
		return (1);
	if (cell_blocked(g, (int)(y + r), (int)(x - r)))
		return (1);
	if (cell_blocked(g, (int)(y + r), (int)(x + r)))
		return (1);
	return (0);
}

static void	dir_to_vec(int dir, double *dx, double *dy)
{
	if (dir == 0)
	{
		*dx = 1.0;
		*dy = 0.0;
	}
	else if (dir == 1)
	{
		*dx = -1.0;
		*dy = 0.0;
	}
	else if (dir == 2)
	{
		*dx = 0.0;
		*dy = 1.0;
	}
	else
	{
		*dx = 0.0;
		*dy = -1.0;
	}
}

static void	move_sprite_wander(t_game *g, t_sprite *s)
{
	double	dx;
	double	dy;
	double	speed;
	double	nx;
	double	ny;
	int		dir;
	int		tries;

	speed = 0.03;
	tries = 0;
	while (tries < 4)
	{
		dir = s->type % 4;
		dir_to_vec(dir, &dx, &dy);
		nx = s->x + dx * speed;
		ny = s->y + dy * speed;
		if (!sprite_collides(g, ny, nx))
		{
			s->x = nx;
			s->y = ny;
			return ;
		}
		s->type++;
		tries++;
	}
}

void	update_sprites_ai(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->sprite_count)
	{
		move_sprite_wander(g, &g->sprites[i]);
		i++;
	}
}