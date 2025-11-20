/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:06:08 by michel            #+#    #+#             */
/*   Updated: 2025/11/18 16:54:45 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"

static int  assign_tex(t_game *g, int idx, const char *path)
{
    if (g->tex_path[idx])
        return (err("texture defined twice"));
    g->tex_path[idx] = ft_strdup(path);
    if (!g->tex_path[idx])
        return (err("malloc"));
    return (0);
}

int parse_elements(t_game *g, char **lines, int *i)
{
    char *line;
    
    while (lines[*i])
    {
        line = ft_strtrim_spaces(lines[*i]);
        if (!line || line[0] == '\0')
        {
            (*i)++;
            continue;
        }
        if (!ft_strncmp(line, "NO ", 3))
        {
            if (assign_tex((g), TEX_N, line + 3))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "SO ", 3))
        {
            if (assign_tex(g, TEX_S, line + 3))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "WE ", 3))
        {
            if (assign_tex(g, TEX_W, line + 3))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "EA ", 3))
        {
            if (assign_tex(g, TEX_E, line + 3))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "F ", 2))
        {
            if (parse_color_line(line + 2, &g->floor_color))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "C ", 2))
        {
            if (parse_color_line(line + 2, &g->ceil_color))
            {
                free(line);
                return (1);
            }
        }
        else if (!ft_strncmp(line, "DO ", 3))
        {
            if (assign_tex(g, TEX_DOOR, line + 3))
            {
                free(line);
                return (1);
            }
        }
        else
            break;
        free(line);
        (*i)++;
    }
    if (!g->tex_path[TEX_N] || !g->tex_path[TEX_S]
        || !g->tex_path[TEX_W] || !g->tex_path[TEX_E])
        return (err("missing texture"));
    if (g->floor_color < 0 || g->ceil_color < 0)
        return (err("missing color"));
    return (0);
}