/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:11:45 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 19:48:36 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

int main(int ac, char **av)
{
    t_game g;

    if (ac != 2)
        return (err("Usage: ./cub3d map.cub"));
    game_init_defaults(&g);
    if (parse_cub_bonus(&g, av[1]))
        return (game_destroy(&g), 1);
    if (game_init_mlx(&g))
        return (game_destroy(&g), 1);
    game_loop_bonus(&g);
    game_destroy(&g);
    return (0);
}