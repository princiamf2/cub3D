/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:31:25 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 15:12:38 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/render.h"

int loop_hook(t_game *g)
{
    handle_input(g);
    render_frame(g);
    return (0);
}

void    game_loop(t_game *g)
{
    mlx_hook(g->win, 2, 1L << 0, key_press, g);
    mlx_hook(g->win, 3, 1L << 1, key_release, g);
    mlx_hook(g->win, 17, 0, close_win, g);
    mlx_loop_hook(g->mlx, loop_hook, g);
    mlx_loop(g->mlx);
}