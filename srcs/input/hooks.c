/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 02:04:10 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 13:48:40 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int key_press(int key, t_game *g)
{
    if (key == XK_w) g->key_w = 1;
    else if (key == XK_s) g->key_s = 1;
    else if (key == XK_a) g->key_a = 1;
    else if (key == XK_d) g->key_d = 1;
    else if (key == XK_Left) g->key_l = 1;
    else if (key == XK_Right) g->key_r = 1;
    else if (key == XK_Escape) return (game_destroy(g), exit(0), 0);
    return (0);
}

int key_release(int key, t_game *g)
{
    if (key == XK_w) g->key_w = 0;
    else if (key == XK_s) g->key_s = 0;
    else if (key == XK_a) g->key_a = 0;
    else if (key == XK_d) g->key_d = 0;
    else if (key == XK_Left) g->key_l = 0;
    else if (key == XK_Right) g->key_r = 0;
    return (0);
}

int close_win(t_game *g)
{
    game_destroy(g);
    exit(0);
    return (0);
}