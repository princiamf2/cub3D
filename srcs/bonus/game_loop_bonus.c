/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:37:20 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 19:38:49 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

int loop_hook_bonus(t_game *g)
{
    handle_input(g);
    render_frame_bonus(g);
    return (0);
}

void game_loop_bonus(t_game *g)
{
    mlx_hook(g->win, 2, 1L << 0, key_press, g);
    mlx_hook(g->win, 3, 1L << 1, key_release, g);
    mlx_hook(g->win, 17, 0, close_win, g);
    mlx_loop_hook(g->mlx, loop_hook_bonus, g);
    mlx_loop(g->mlx);
}