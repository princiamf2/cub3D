/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:24:16 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 16:41:23 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void destroy_texture(t_game *g)
{
    int i;

    i = 0;
    while (i < TEX_COUNT)
    {
        if (g->tex[i].img)
            mlx_destroy_image(g->mlx, g->tex[i].img);
        if (g->tex_path[i])
            free(g->tex_path[i]);
        i++;
    }
}

void    game_destroy(t_game *g)
{
    int y;

    if (g->map.grid)
    {
        y = 0;
        while (y < g->map.height)
        {
            free(g->map.grid[y]);
            y++;
        }
        free(g->map.grid);
    }
    if (g->zbuffer)
        free(g->zbuffer);
    destroy_texture(g);
    if (g->frame)
        mlx_destroy_image(g->mlx, g->frame);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->sprite_tex.img)
		mlx_destroy_image(g->mlx, g->sprite_tex.img);
    if (g->mlx)
    {
        mlx_destroy_display(g->mlx);
        free(g->mlx);
    }
}