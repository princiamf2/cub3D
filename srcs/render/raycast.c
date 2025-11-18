/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:08:53 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 14:02:07 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/render.h"

static void ray_init(t_game *g, int x, t_ray *r)
{
    r->camera_x = 2.0 * x / (double)g->scr_w - 1.0;
    r->ray_dir_x = cos(g->player.dir) + g->player.plane_x * r->camera_x;
    r->ray_dir_y = sin(g->player.dir) + g->player.plane_y * r->camera_x;
    r->map_x = (int)g->player.x;
    r->map_y = (int)g->player.y;
    r->delta_dist_x = (r->ray_dir_x == 0.0) ? BIG : fabs(1.0 / r->ray_dir_x);
    r->delta_dist_y = (r->ray_dir_y == 0.0) ? BIG : fabs(1.0 / r->ray_dir_y);
    r->hit = 0;
}

static void	ray_step_setup(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0.0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0.0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.y) * r->delta_dist_y;
	}
}

static int	inside_map(t_game *g, int mx, int my)
{
	if (my < 0 || my >= g->map.height)
		return (0);
	if (mx < 0 || mx >= g->map.width)
		return (0);
	return (1);
}

static void	ray_dda(t_game *g, t_ray *r)
{
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (!inside_map(g, r->map_x, r->map_y))
			break ;
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	ray_finish_geometry(t_game *g, t_ray *r)
{
	if (r->hit == 0)
	{
		r->perp_wall_dist = BIG;
		r->line_h = 0;
		r->draw_start = 0;
		r->draw_end = 0;
		return ;
	}
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.x
				+ (1 - r->step_x) / 2.0) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.y
				+ (1 - r->step_y) / 2.0) / r->ray_dir_y;
	r->line_h = (int)(g->scr_h / r->perp_wall_dist);
	r->draw_start = -r->line_h / 2 + g->scr_h / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + g->scr_h / 2;
	if (r->draw_end >= g->scr_h)
		r->draw_end = g->scr_h - 1;
	if (r->side == 0)
		r->wall_x = g->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = g->player.x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
}

void	raycast_column(t_game *g, int x)
{
	t_ray	r;

	ray_init(g, x, &r);
	ray_step_setup(g, &r);
	ray_dda(g, &r);
	ray_finish_geometry(g, &r);
	draw_wall_stripe(g, x, &r);
	g->zbuffer[x] = r.perp_wall_dist;
}