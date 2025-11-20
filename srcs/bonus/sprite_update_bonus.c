/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:39:12 by michel            #+#    #+#             */
/*   Updated: 2025/11/20 02:40:52 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	animate_sprites(t_game *g)
{
	int	i;

	g->sprite_anim_tick++;
	if (g->sprite_anim_tick < 12)
		return ;
	g->sprite_anim_tick = 0;
	i = 0;
	while (i < g->sprite_count)
	{
		g->sprites[i].anim_frame++;
		if (g->sprites[i].anim_frame >= 3)
			g->sprites[i].anim_frame = 0;
		i++;
	}
}

void	update_sprites_from_player(t_game *g)
{
	int		i;
	int		j;
	double	dx;
	double	dy;

    update_sprites_ai(g);
	i = 0;
	while (i < g->sprite_count)
	{
		dx = g->sprites[i].x - g->player.x;
		dy = g->sprites[i].y - g->player.y;
		g->sprites[i].dist = dx * dx + dy * dy;
		i++;
	}
	i = 0;
	while (i < g->sprite_count - 1)
	{
		j = i + 1;
		while (j < g->sprite_count)
		{
			if (g->sprites[i].dist < g->sprites[j].dist)
				swap_sprites(&g->sprites[i], &g->sprites[j]);
			j++;
		}
		i++;
	}
	animate_sprites(g);
}