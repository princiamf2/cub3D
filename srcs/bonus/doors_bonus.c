/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:06:38 by michel            #+#    #+#             */
/*   Updated: 2025/11/20 02:35:29 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/sprite_bonus.h"

void init_doors_from_map(t_game *g)
{
    int x;
    int y;

    g->door_count = 0;
    y = 0;
    while (y < g->map.height)
    {
        x = 0;
        while (x < g->map.width)
        {
            if (g->map.grid[y][x] == 'D' && g->door_count < MAX_DOOR)
            {
                g->doors[g->door_count].x = x;
                g->doors[g->door_count].y = y;
                g->doors[g->door_count].open = 0;
                g->doors[g->door_count].frame = 0;
                g->doors[g->door_count].anim_dir = 0;
                g->door_count++;
            }
            x++;
        }
        y++;
    }
}

int is_doors_ceil_closed(t_game *g, int my, int mx)
{
    int i;

    i = 0;
    while (i < g->door_count)
    {
        if (g->doors[i].x == mx && g->doors[i].y == my)
        {
            if (g->doors[i].open == 0)
                return (1);
            return (0);
        }
        i++;
    }
    return (0);
}

void try_use_door(t_game *g)
{
    double dir_x;
    double dir_y;
    double dist;
    int mx;
    int my;
    int i;

    dir_x = cos(g->player.dir);
    dir_y = sin(g->player.dir);
    dist = 0.8;
    mx = (int)(g->player.x + dir_x * dist);
    my = (int)(g->player.y + dir_y * dist);
    i = 0;
    while (i < g->door_count)
    {
        if (g->doors[i].x == mx && g->doors[i].y == my)
        {
            if (g->doors[i].anim_dir == 0)
            {
                if (g->doors[i].open)
                    g->doors[i].anim_dir = -1;
                else
                    g->doors[i].anim_dir = 1;
            }
            return ;
        }
        i++;
    }
}

void    update_doors_anim(t_game *g)
{
    int i;
    
    i = 0;
    while (i < g->door_count)
    {
        if (g->doors[i].anim_dir != 0)
        {
            g->doors[i].frame += g->doors[i].anim_dir;
            if (g->doors[i].frame <= 0)
            {
                g->doors[i].frame = 0;
                g->doors[i].anim_dir = 0;
                g->doors[i].open = 0;
            }
            else if (g->doors[i].frame >= DOOR_FRAMES - 1)
            {
                g->doors[i].frame = DOOR_FRAMES - 1;
                g->doors[i].anim_dir = 0;
                g->doors[i].open = 1;
            }
        }
        i++;
    }
}

t_door  *get_door_of_cell(t_game *g, int mx, int my)
{
    int i;
    
    i = 0;
    while (i < g->door_count)
    {
        if (g->doors[i].x == mx && g->doors[i].y == my)
            return (&g->doors[i]);
        i++;
    }
    return (NULL);
}