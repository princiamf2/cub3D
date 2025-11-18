/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:27:45 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 19:24:36 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/render.h"

void render_frame(t_game *g)
{
    int x;

    x = 0;
    while (x < g->scr_w)
    {
        raycast_column(g, x);
        x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->frame, 0, 0);
}