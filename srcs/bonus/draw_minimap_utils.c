/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 03:08:14 by michel            #+#    #+#             */
/*   Updated: 2025/11/21 03:10:23 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sprite_bonus.h"

static void	mm_draw_sprite_dot(t_game *g, int cx, int cy)
{
	int	r;
	int	dx;
	int	dy;

	r = MM_TILE / 4;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				mm_put_pixel(g, cx + dx, cy + dy, 0x0000FFFF);
			dx++;
		}
		dy++;
	}
}

static void	mm_draw_one_sprite(t_game *g, t_sprite *s)
{
	int	px;
	int	py;
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	px = (int)g->player.x;
	py = (int)g->player.y;
	dx = (int)s->x - px;
	dy = (int)s->y - py;
	if (dx < -MM_RADIUS || dx > MM_RADIUS)
		return ;
	if (dy < -MM_RADIUS || dy > MM_RADIUS)
		return ;
	cx = MM_OFFSET_X + (dx + MM_RADIUS) * MM_TILE + MM_TILE / 2;
	cy = MM_OFFSET_Y + (dy + MM_RADIUS) * MM_TILE + MM_TILE / 2;
	mm_draw_sprite_dot(g, cx, cy);
}

void	mm_draw_sprites(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->sprite_count)
	{
		mm_draw_one_sprite(g, &g->sprites[i]);
		i++;
	}
}