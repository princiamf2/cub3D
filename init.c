/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:47:41 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 14:22:02 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void game_init_defaults(t_game *game)
{
    ft_bzero(game, sizeof(*game));
    game->frame.w = WIN_W;
    game->frame.h = WIN_H;
}

static int load_tex(t_game *game, int i, char *path)
{
    int w;
    int h;

    game->ex[i].img = mlx_xpm_file_to_image(game->mlx, path, &w, &h);
    if (!game->ex[i].img)
        return (err("failed to load texture"));
    game->ex[i].w = w;
    game->ex[i].h = h;
    game->ex[i].addr = mlx_get_data_addr(game->ex[i].img, &game->ex[i].bpp, &game->ex[i].line_len, &game->ex[i].endian);
    game->ex[i].path = ft_strdup(path);
    return (0); 
}

int load_texture(t_game *game)
{
    if (load_tex(game, TEX_NO, game->cfg.no))
        return (1);
    if (load_tex(game, TEX_SO, game->cfg.so))
        return (1);
    if (load_tex(game, TEX_WE, game->cfg.we))
        return (1);
    if (load_tex(game, TEX_EA, game->cfg.ea))
        return (1);
    return (0);
}

int game_init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (err("mlx_init failed"));
    game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3d");
    if (!game->win)
        return (err("mlx_new_win failed"));
    game->frame.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!game->frame.img)
        return (err("mlx_new_image failed"));
    game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp, &game->frame.line_len, &game->frame.endian);
    game->zbuf = (double *)malloc(sizeof(double) * game->frame.w);
    if (!game->zbuf)
        return (err("zbuffer alloc failed"));
    if (load_sprite(game, &game->enemy_s, "textures/test.xpm", 3, 4))
        return (1);
    return (0);
}

void set_player_from_spawn(t_game *g)
{
    g->pl.x = g->cfg.spawn_x + 0.5;
    g->pl.y = g->cfg.spawn_y + 0.5;
    if (g->cfg.spawn_dir == 'N')
    {
        g->pl.dirx = 0;
        g->pl.diry = -1;
        g->pl.planex = 0.66;
        g->pl.planey = 0;
    }
    else if (g->cfg.spawn_dir == 'S')
    {
        g->pl.dirx = 0;
        g->pl.diry = 1;
        g->pl.planex = -0.66;
        g->pl.planey = 0;
    }
    else if (g->cfg.spawn_dir == 'E')
    {
        g->pl.dirx = 1;
        g->pl.diry = 0;
        g->pl.planex = 0;
        g->pl.planey = 0.66;
    }
    else if (g->cfg.spawn_dir == 'W')
    {
        g->pl.dirx = -1;
        g->pl.diry = 0;
        g->pl.planex = 0;
        g->pl.planey = -0.66;
    }
}