/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:41:03 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 22:49:17 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int  load_one_tex(t_game *g, int i)
{
    t_tex *t;
    
    write(2, "Loading tex: ", 13);
    write(2, g->tex_path[i], ft_strlen(g->tex_path[i]));
    write(2, "\n", 1);
    
    t = &g->tex[i];
    t->img = mlx_xpm_file_to_image(g->mlx, g->tex_path[i], &t->w, &t->h);
    if (!t->img)
        return (err("mlx_xpm_to_image failed"));
    t->data = (int *)mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
    if (!t->data)
        return (err("mlx_get_data_addr failed"));
    return (0);
}

int game_init_mlx(t_game *g)
{
    int i;
    int bpp;
    int ll;
    int endian;

    g->mlx = mlx_init();
    if (!g->mlx)
        return (err("mlx_init failed"));
    g->win = mlx_new_window(g->mlx, g->scr_w, g->scr_h, "cub3d");
    if (!g->win)
        return (err("mlx_new_window failed"));
    g->frame = mlx_new_image(g->mlx, g->scr_w, g->scr_h);
    if (!g->frame)
        return (err("mlx_new_image failed"));
    g->frame_data = (int *)mlx_get_data_addr(g->frame, &bpp, &ll, &endian);
    g->zbuffer = (double *)malloc(sizeof(double) * g->scr_w);
    if (!g->zbuffer)
        return (err("malloc zbuffer"));
    i = 0;
    while (i < TEX_COUNT)
    {
        if (load_one_tex(g, i))
            return (1);
        i++;
    }
    g->sprite_tex.img = mlx_xpm_file_to_image(
			g->mlx, SPRITE_XPM_PATH,
			&g->sprite_tex.w, &g->sprite_tex.h);
	if (!g->sprite_tex.img)
		return (err("mlx_xpm_to_image sprite failed"));
	g->sprite_tex.data = (int *)mlx_get_data_addr(
			g->sprite_tex.img, &g->sprite_tex.bpp,
			&g->sprite_tex.line_len, &g->sprite_tex.endian);
	if (!g->sprite_tex.data)
		return (err("mlx_get_data_addr sprite failed"));
    g->sprite_tex.frame_w = g->sprite_tex.w / 3;
    g->sprite_tex.frame_h = g->sprite_tex.h / 4;
    g->sprite_tex.frames = 3;
    return (0);
}