/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 21:15:14 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 17:07:40 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_mapline(char *s)
{
    int i;

    i = 0;
    if (!s[0])
        return (0);
    while (s[i])
    {
        if (s[i] == '0' || s[i] == '1' || s[i] == ' ')
            ;
        else if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
            ;
        else if (s[i] == 'D')
            ;
        else
            return (0);
        i++; 
    }
    return (1);
}

void measure_map(char **lines, int i, int n, int *h, int *w)
{
    int k;
    int width;
    int len;
    
    k = i;
    width = 0;
    *h = 0;
    while (k < n && is_mapline(lines[k]) && lines[k][0])
    {
        len = (int)ft_strlen(lines[k]);
        if (len > width)
            width = len;
        (*h)++;
        k++;
    }
    *w = width;
}

int copy_map(t_game *g, char **lines, int i, int h, int w)
{
    int r;
    int c;
    int len;

    g->map.height = h;
    g->map.width = w;
    g->map.grid = (char **)ft_calloc(h + 1, sizeof(char *));
    if (!g->map.grid)
        return (1);
    r = 0;
    while (r < h)
    {
        g->map.grid[r] = (char *)ft_calloc(w + 1, 1);
        if (!g->map.grid[r])
            return (1);
        ft_memcpy(g->map.grid[r], lines[i + r], ft_strlen(lines[i + r]));
        len = (int)ft_strlen(lines[i + r]);
        while (len < w)
        {
            g->map.grid[r][len] = ' ';
            len++;
        }
        c = 0;
        while (c < w)
        {
            if (g->map.grid[r][c] == 'N' || g->map.grid[r][c] == 'S' || g->map.grid[r][c] == 'W' || g->map.grid[r][c] == 'E')
            {
                if (g->cfg.have_player)
                        return (err("multiple player spawns"));
                    
                g->cfg.have_player = 1;
                g->cfg.spawn_dir = g->map.grid[r][c];
                g->cfg.spawn_x = c;
                g->cfg.spawn_y = r;
                g->map.grid[r][c] = '0';
            }
            else if (g->map.grid[r][c] == 'D')
            {
                if (g->cfg.have_enemy)
                    return (err("duplicate enemy D"));
                g->enemy.x = c + 0.5;
                g->enemy.y = r + 0.5;
                if ((int)g->enemy.x == g->cfg.spawn_x && (int)g->enemy.y == g->cfg.spawn_y)
                    g->enemy.x += 1;
                g->enemy.vx = 1.0;
                g->enemy.vy = 0.0;
                g->enemy.last_ms = now_ms();
                g->enemy.moving = 1;
                g->cfg.have_enemy = 1;
                g->cfg.enemy_count++;
                g->map.grid[r][c] = '0';
            }
            c++;
        }
        r++;
    }
    return (0);
}

int parse_map_block(t_game *game, char **lines, int i, int n)
{
    int h;
    int w;
    
    measure_map(lines, i, n, &h, &w);
    if (h <= 0)
        return (err("empty map"));
    if (copy_map(game, lines, i, h, w))
        return (1);
    return (0);
}

int is_wall_or_space(char c)
{
    return (c == '1' || c == ' ');
}


