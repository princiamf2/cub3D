/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:06:05 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 13:20:46 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void game_destroy(t_game *game)
{
    int y;
    
    if (game->ex[TEX_NO].img)
        mlx_destroy_image(game->mlx, game->ex[TEX_NO].img);
    if (game->ex[TEX_SO].img)
        mlx_destroy_image(game->mlx, game->ex[TEX_SO].img);
    if (game->ex[TEX_WE].img)
        mlx_destroy_image(game->mlx, game->ex[TEX_WE].img);
    if (game->ex[TEX_EA].img)
        mlx_destroy_image(game->mlx, game->ex[TEX_EA].img);
    if (game->frame.img)
        mlx_destroy_image(game->mlx, game->frame.img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
        mlx_destroy_display(game->mlx);
    if (game->enemy_s.img)
	    mlx_destroy_image(game->mlx, game->enemy_s.img);
    if (game->zbuf)
	    free(game->zbuf);
    free(game->mlx);
    free(game->cfg.no);
    free(game->cfg.so);
    free(game->cfg.we);
    free(game->cfg.ea);
    if (game->map.grid)
    {
        y = 0;
        while (y < game->map.height)
        {
            free(game->map.grid[y]);
            y++;
        }
        free(game->map.grid);
    }
}