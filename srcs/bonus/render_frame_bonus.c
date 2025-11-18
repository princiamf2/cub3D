/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:07:49 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 19:24:58 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/render.h"
#include "../../includes/sprite_bonus.h"

void render_frame_bonus(t_game *g)
{
    int x;

    x = 0;
    while (x < g->scr_w)
    {
        raycast_column(g, x);
        x++;
    }
    draw_sprites(g);
    mlx_put_image_to_window(g->mlx, g->win, g->frame, 0, 0);
}