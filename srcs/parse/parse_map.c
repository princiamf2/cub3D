/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:01:38 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 13:55:13 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"

static int is_map_line(const char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    if (*s == '1' || *s == '0' || *s == 'N' 
        || *s == 'S' || *s == 'E' || *s == 'W')
        return (1);
    return (0);
}

int parse_map(t_game *g, char **lines, int start)
{
    int count;
    int y;

    count = 0;
    while (lines[start + count] && is_map_line(lines[start + count]))
        count++;
    if (count == 0)
        return (err("no map"));
    g->map.grid = (char **)malloc(sizeof(char *) * count);
    if (!g->map.grid)
        return (err("malloc"));
    g->map.height = count;
    g->map.width = 0;
    y = 0;
    while (y < count)
    {
        g->map.grid[y] = ft_strdup(lines[start + y]);
        if (!g->map.grid[y])
            return (err("malloc"));
        if ((int)ft_strlen(g->map.grid[y]) > g->map.width)
            g->map.width = ft_strlen(g->map.grid[y]);
        y++;
    }
    return (0);
}

int	rectify_map(t_map *map)
{
	int		y;
	char	*new;
	int		x;

	y = 0;
	while (y < map->height)
	{
		if ((int)ft_strlen(map->grid[y]) < map->width)
		{
			new = (char *)malloc(map->width + 1);
			if (!new)
				return (1);
			x = 0;
			while (map->grid[y][x])
			{
				new[x] = map->grid[y][x];
				x++;
			}
			while (x < map->width)
				new[x++] = ' ';
			new[x] = '\0';
			free(map->grid[y]);
			map->grid[y] = new;
		}
		y++;
	}
	return (0);
}