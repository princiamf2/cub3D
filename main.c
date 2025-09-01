/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:34:32 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 13:03:02 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int usage(void)
{
    write(2, "Usage: ./cub3D <map.cub>\n", 25);
    return (1);
}

int main(int ac, char **av)
{
    t_game g;

    if (ac != 2)
        return (usage());
    game_init_defaults(&g);
    if (parse_cub(&g, av[1]))
        return (game_destroy(&g), 1);
    if (game_init_mlx(&g))
        return (game_destroy(&g), 1);
    if (load_texture(&g))
        return (game_destroy(&g), 1);
    set_player_from_spawn(&g);
    mlx_hook(g.win, 2, 1L << 0, on_key_press, &g);
    mlx_hook(g.win, 17, 0, on_destroy, &g);
    mlx_loop_hook(g.mlx, (int (*)(void *))game_render, &g);
    g.running = 1;
    mlx_loop(g.mlx);
    game_destroy(&g);
    return (0);
}