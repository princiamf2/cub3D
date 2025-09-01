/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:43:06 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 13:06:17 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_empty(char *s)
{
    int i;
    
    i = 0;
    while (s[i] && ft_isspace((unsigned char)s[i]))
        i++;
    return (s[i] == '\0');
}

int parse_cub(t_game *game, char *path)
{
    char *buf;
    char **lines;
    int n;
    int i;
    int map_started;

    buf = read_all(path);
    if (!buf)
        return (err("could not read file"));
    lines = split_lines_keep(buf, &n);
    if (!lines || n == 0)
        return (xfree(buf), err("empty file"));
    i = 0;
    map_started = 0;
    while (i < n)
    {
        lines[i] = trim_inplace(lines[i]);
        if (!map_started && is_mapline(lines[i]))
        {
            if (parse_map_block(game, lines, i, n))
                return (xfree(buf), free_split(lines), 1);
            map_started = 1;
            break;
        }
        else if (!map_started && !is_empty(lines[i]))
        {
            if (parse_kv_line(game, lines[i]))
                return (xfree(buf), free_split(lines), 1);
        }
        i++;
    }
    if (!game->cfg.no || !game->cfg.so || !game->cfg.we || !game->cfg.ea)
        return (xfree(buf), free_split(lines), err("missing texture path"));
    if (!game->cfg.have_player)
        return (xfree(buf), free_split(lines), err("missing player spawn"));
    if (validate_map_closed(&game->map))
        return (xfree(buf), free_split(lines), 1);
    xfree(buf);
    free_split(lines);
    return (0);
}