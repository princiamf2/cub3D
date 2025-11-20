/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:06:38 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 13:49:45 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int bad_neighbor(t_map *m, int y, int x)
{
    if (y <= 0 || x <= 0 || y >= m->height - 1 || x >= m->width - 1)
        return (1);
    if (m->grid[y - 1][x] == ' ')
        return (1);
    if (m->grid[y + 1][x] == ' ')
        return (1);
    if (m->grid[y][x - 1] == ' ')
        return (1);
    if (m->grid[y][x + 1] == ' ')
        return (1);
    return (0);
}

int check_map_closed(t_map *map, t_player *p)
{
    int y;
    int x;
    
    p->x = -1;
    p->y = -1;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == '0')
            {
                if (bad_neighbor(map, y, x))
                    return (1);
            }
            else if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
                || map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
            {
                if (bad_neighbor(map, y, x))
                    return (1);
                p->x = x + 0.5;
                p->y = y + 0.5;
                if (map->grid[y][x] == 'N')
                    p->dir = -M_PI_2;
                else if (map->grid[y][x] == 'S')
                    p->dir = M_PI_2;
                else if (map->grid[y][x] == 'E')
                    p->dir = 0;
                else
                    p->dir = M_PI;
                map->grid[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    if (p->x < 0)
        return  (err("no player"));
    p->plane_x = -sin(p->dir) * 0.66;
    p->plane_y = cos(p->dir) * 0.66;
    return (0);
}