/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:57:00 by michel            #+#    #+#             */
/*   Updated: 2025/11/18 11:52:02 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static int	get_dir_index(t_game *g, t_sprite *s)
{
	double	mv_x;
	double	mv_y;
	double	fx;
	double	fy;
	double	rx;
	double	ry;
	double	mv_forward;
	double	mv_right;
	int		dir;

	/* vecteur de déplacement du sprite d’après s->type (même logique que dir_to_vec) */
	dir = s->type % 4;
	if (dir == 0)
	{
		mv_x = 1.0;
		mv_y = 0.0;
	}
	else if (dir == 1)
	{
		mv_x = -1.0;
		mv_y = 0.0;
	}
	else if (dir == 2)
	{
		mv_x = 0.0;
		mv_y = 1.0;
	}
	else
	{
		mv_x = 0.0;
		mv_y = -1.0;
	}

	/* base caméra : forward = direction du joueur, right = plane */
	fx = cos(g->player.dir);
	fy = sin(g->player.dir);
	rx = g->player.plane_x;
	ry = g->player.plane_y;

	/* composantes du mouvement dans la base caméra */
	mv_forward = mv_x * fx + mv_y * fy;
	mv_right = mv_x * rx + mv_y * ry;

	/* on choisit la ligne en fonction de la direction à l’écran */
	if (fabs(mv_forward) >= fabs(mv_right))
	{
		if (mv_forward >= 0.0)
			return (SPRITE_ROW_BACK);
		else
			return (SPRITE_ROW_FRONT);
	}
	else
	{
		if (mv_right > 0.0)
			return (SPRITE_ROW_LEFT);
		else
			return (SPRITE_ROW_RIGHT);
	}
}

static void	sprite_project(t_game *g, t_sprite *s, t_sprite_proj *p)
{
	double	dir_x;
	double	dir_y;
	double	inv_det;
	double	base_h;
	double	bottom;
	double	ratio;

	dir_x = cos(g->player.dir);
	dir_y = sin(g->player.dir);
	p->sprite_x = s->x - g->player.x;
	p->sprite_y = s->y - g->player.y;
	inv_det = 1.0 / (g->player.plane_x * dir_y
			- dir_x * g->player.plane_y);
	p->transform_x = inv_det * (dir_y * p->sprite_x
			- dir_x * p->sprite_y);
	p->transform_y = inv_det * (-g->player.plane_y * p->sprite_x
			+ g->player.plane_x * p->sprite_y);
	p->screen_x = (int)((g->scr_w / 2.0)
			* (1.0 + p->transform_x / p->transform_y));
	base_h = fabs((double)g->scr_h / p->transform_y);
	ratio = (double)g->sprite_tex.frame_w / (double)g->sprite_tex.frame_h;
	p->height = (int)(base_h * SPRITE_SCALE);
	p->width = (int)(p->height * ratio);
	bottom = g->scr_h / 2.0 + base_h / 2.0;
	p->draw_end_y = (int)bottom;
	if (p->draw_end_y >= g->scr_h)
		p->draw_end_y = g->scr_h - 1;
	p->draw_start_y = p->draw_end_y - p->height;
	if (p->draw_start_y < 0)
		p->draw_start_y = 0;
	p->draw_start_x = -p->width / 2 + p->screen_x;
	if (p->draw_start_x < 0)
		p->draw_start_x = 0;
	p->draw_end_x = p->width / 2 + p->screen_x;
	if (p->draw_end_x >= g->scr_w)
		p->draw_end_x = g->scr_w - 1;
}

static void	sprite_draw_stripe(t_game *g, t_sprite_proj *p,
				t_sprite *s, int stripe)
{
	int		tex_x;
	int		y;
	int		tex_y;
	int		color;
	int		row;
	int		col;
	int		frame_x;
	int		frame_y;
	int		screen_h;
	double	step;
	double	tex_pos;

	if (p->transform_y <= 0.0 || stripe < 0 || stripe >= g->scr_w)
		return ;
	if (p->transform_y >= g->zbuffer[stripe])
		return ;
	tex_x = (int)((stripe - p->draw_start_x)
			* g->sprite_tex.frame_w / p->width);
	if (tex_x < 0 || tex_x >= g->sprite_tex.frame_w)
		return ;
	/* lignes = direction, colonnes = animation */
	row = get_dir_index(g, s);
	col = s->anim_frame;
	if (col < 0)
		col = 0;
	if (col >= g->sprite_tex.frames)
		col = g->sprite_tex.frames - 1;
	screen_h = p->draw_end_y - p->draw_start_y + 1;
	step = (double)g->sprite_tex.frame_h / (double)screen_h;
	tex_pos = 0.0;
	y = p->draw_start_y;
	while (y <= p->draw_end_y)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= g->sprite_tex.frame_h)
			tex_y = g->sprite_tex.frame_h - 1;
		frame_x = col * g->sprite_tex.frame_w + tex_x;
		frame_y = row * g->sprite_tex.frame_h + tex_y;
		color = g->sprite_tex.data[frame_y * g->sprite_tex.w + frame_x];
		if ((color & 0x00FFFFFF) != 0x00000000)
			g->frame_data[y * g->scr_w + stripe] = color;
		tex_pos += step;
		y++;
	}
}

static void	draw_one_sprite(t_game *g, t_sprite *s)
{
	t_sprite_proj	p;
	int				stripe;

	sprite_project(g, s, &p);
	if (p.transform_y <= 0.0001)
		return ;
	stripe = p.draw_start_x;
	while (stripe <= p.draw_end_x)
	{
		sprite_draw_stripe(g, &p, s, stripe);
		stripe++;
	}
}

void	draw_sprites(t_game *g)
{
	int	i;

	if (!g->sprite_tex.img || g->sprite_count <= 0)
		return ;
	update_sprites_from_player(g);
	i = 0;
	while (i < g->sprite_count)
	{
		draw_one_sprite(g, &g->sprites[i]);
		i++;
	}
}