/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 22:35:42 by michel            #+#    #+#             */
/*   Updated: 2025/08/21 23:08:00 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_map_closed(t_map *m)
{
    int x;
    int y;
    
    x = 0;
    while (x < m->width)
    {
        if (!is_wall_or_space(m->grid[0][x]) || !is_wall_or_space(m->grid[m->height - 1][x]))
            return (err("map not closed (top/bottom)"));
        x++;
    }
    y = 0;
    while (y < m->height)
    {
        if (!is_wall_or_space(m->grid[y][0]) || !is_wall_or_space(m->grid[y][m->width - 1]))
            return (err("map not closed (left/right)"));
        y++;
    }
    y = 1;
    while (y < m->height - 1)
    {
        x = 1;
        while (x < m->width - 1)
        {
            if (m->grid[y][x] == '0')
            {
                if (m->grid[y - 1][x] == ' '
                    || m->grid[y + 1][x] == ' '
                    || m->grid[y][x - 1] == ' '
                    || m->grid[y][x + 1] == ' ')
                    return (err("map has hole"));
            }
            x++;
        }
        y++;
    }
    return (0);
}