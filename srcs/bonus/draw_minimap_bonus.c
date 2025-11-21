/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:24:12 by michel            #+#    #+#             */
/*   Updated: 2025/11/21 03:15:36 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sprite_bonus.h"

void	mm_put_pixel(t_game *g, int x, int y, int color)
{
	if (x < 0 || x >= g->scr_w || y < 0 || y >= g->scr_h)
		return ;
	g->frame_data[y * g->scr_w + x] = color;
}

static void	mm_draw_tile(t_game *g, int px, int py, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MM_TILE)
	{
		dx = 0;
		while (dx < MM_TILE)
		{
			mm_put_pixel(g, px + dx, py + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	mm_draw_player(t_game *g)
{
	int	cx;
	int	cy;
	int	r;
	int	dx;
	int	dy;

	cx = MM_OFFSET_X + MM_RADIUS * MM_TILE + MM_TILE / 2;
	cy = MM_OFFSET_Y + MM_RADIUS * MM_TILE + MM_TILE / 2;
	r = MM_TILE / 3;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				mm_put_pixel(g, cx + dx, cy + dy, 0x00FF0000);
			dx++;
		}
		dy++;
	}
}

static int	get_cell_color(t_game *g, int my, int mx)
{
	char	c;

	if (my < 0 || my >= g->map.height || mx < 0 || mx >= g->map.width)
		return (0x00000000);
	c = g->map.grid[my][mx];
	if (c == '1')
		return (0x00444444);
	if (c == '0')
		return (0x00999999);
	if (c == 'D')
	{
		if (is_doors_ceil_closed(g, my, mx))
			return (0x00CCCC00);
		return (0x00FFAA00);
	}
	return (0x00000000);
}

void	draw_minimap_bonus(t_game *g)
{
	int	p_x;
	int	p_y;
	int	dy;
	int	dx;
	int	color;

	p_x = (int)g->player.x;
	p_y = (int)g->player.y;
	dy = -MM_RADIUS;
	while (dy <= MM_RADIUS)
	{
		dx = -MM_RADIUS;
		while (dx <= MM_RADIUS)
		{
			color = get_cell_color(g, p_y + dy, p_x + dx);
			if (color != 0x00000000)
				mm_draw_tile(g,
					MM_OFFSET_X + (dx + MM_RADIUS) * MM_TILE,
					MM_OFFSET_Y + (dy + MM_RADIUS) * MM_TILE,
					color);
			dx++;
		}
		dy++;
	}
	mm_draw_sprites(g);
	mm_draw_player(g);
}