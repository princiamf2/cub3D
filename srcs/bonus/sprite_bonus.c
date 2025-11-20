/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:15:47 by michel            #+#    #+#             */
/*   Updated: 2025/11/20 02:31:36 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

static int add_sprite(t_game *g, int x, int y)
{
    t_sprite *sprite;

    if (g->sprite_count >= MAX_SPRITES)
        return (err("too many sprite"));
    sprite = &g->sprites[g->sprite_count];
    sprite->x = x +0.5;
    sprite->y = y + 0.5;
    sprite->dist = 0.0;
    sprite->anim_frame = 0;
    sprite->type = (x + y) % 4;
    g->sprite_count++;
    return (0);
}

void    init_sprites_from_map(t_game *g)
{
    int y;
    int x;

    g->sprite_count = 0;
    y = 0;
    while (y < g->map.height)
    {
        x = 0;
        while (x < g->map.width)
        {
            if (g->map.grid[y][x] == '2')
            {
                if (add_sprite(g, x, y))
                    return ;
                g->map.grid[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}