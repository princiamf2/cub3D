/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_kv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 23:30:23 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 13:07:11 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *dup_after(char *s, int k)
{
    while (s[k] == ' ' || s[k] == '\t')
        k++;
    return (ft_strdup(s + k));
}

int parse_kv_line(t_game *game, char *line)
{
    if (!ft_strncmp(line, "NO ", 3) && !game->cfg.no)
        game->cfg.no = dup_after(line, 2);
    else if (!ft_strncmp(line, "SO ", 3) && !game->cfg.so)
        game->cfg.so = dup_after(line, 2);
    else if (!ft_strncmp(line, "WE ", 3) && !game->cfg.we)
        game->cfg.we = dup_after(line, 2);
    else if (!ft_strncmp(line, "EA ", 3) && !game->cfg.ea)
        game->cfg.ea = dup_after(line, 2);
    else if (!ft_strncmp(line, "F ", 2))
        return (parse_rgb(line + 2, &game->cfg.floor));
    else if (!ft_strncmp(line, "C ", 2))
        return (parse_rgb(line + 2, &game->cfg.ceil));
    else
        return (err("unknown identifier"));
    return (0);
}