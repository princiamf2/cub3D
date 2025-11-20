/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:52:54 by michel            #+#    #+#             */
/*   Updated: 2025/11/20 02:39:39 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/render.h"
#include "../../includes/sprite_bonus.h"

int	compute_door_tex_x(t_game *g, t_ray *r, t_tex *tex)
{
	t_door	*d;
	int		frame;
	int		frame_w;
	int		base_x;
	int		tex_x;

	d = get_door_of_cell(g, r->map_x, r->map_y);
	frame = 0;
	if (d != NULL)
		frame = d->frame;
	if (frame < 0)
		frame = 0;
	if (frame >= DOOR_FRAMES)
		frame = DOOR_FRAMES - 1;
	frame_w = tex->frame_w;
	base_x = frame * frame_w + DOOR_INNER_MIN;
	tex_x = base_x + (int)(r->wall_x * (double)DOOR_INNER_W);
	if (tex_x < base_x)
		tex_x = base_x;
	if (tex_x >= base_x + DOOR_INNER_W)
		tex_x = base_x + DOOR_INNER_W - 1;
	return (tex_x);
}

int compute_normal_tex_x(t_tex *tex, t_ray *r)
{
    int tex_x;

    tex_x = (int)(r->wall_x * (double)tex->w);
    if (r->side == 0 && r->ray_dir_x > 0.0)
        tex_x = tex->w - tex_x - 1;
    if (r->side == 1 && r->ray_dir_y < 0.0)
        tex_x = tex->w - tex_x - 1;
    return (tex_x);
}

int compute_tex_x(t_game *g, t_ray *r, t_tex *tex)
{
    if (tex == &g->tex[TEX_DOOR])
        return (compute_door_tex_x(g, r, tex));
    return (compute_normal_tex_x(tex, r));
}