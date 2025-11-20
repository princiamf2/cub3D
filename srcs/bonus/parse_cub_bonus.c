/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:28:55 by michel            #+#    #+#             */
/*   Updated: 2025/11/18 14:32:05 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"
#include "../../includes/sprite_bonus.h"

int parse_cub_bonus(t_game *g, const char *path)
{
    int fd;
    char **lines;
    int i;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (err("cannot open .cub"));
    lines = split_lines_from_fd(fd, NULL);
    close(fd);
    if (!lines)
        return (err("cannot read .cub"));
    i = 0;
    if (parse_elements(g, lines, &i))
        return (free_lines(lines), 1);
    if (parse_map(g, lines, i))
        return (free_lines(lines), 1);
    if (rectify_map(&g->map))
        return (free_lines(lines), err("map rectify_failed"));
    init_sprites_from_map(g);
    init_doors_from_map(g);
    if (check_map_closed(&g->map, &g->player))
        return (free_lines(lines), err("map not closed"));
    return (0);
}