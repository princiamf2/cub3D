/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:36:52 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 13:50:57 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/parse.h"

static int parse_one(const char *s, int *out)
{
    int ok;
    int v;

    v = ft_atoi_strict(s, &ok);
    if (!ok || v < 0 || v > 255)
        return (1);
    *out = v;
    return (0);
}

int parse_color_line(const char *s, int *out_color)
{
    char    *tmp;
    char    *p1;
    char    *p2;
    int     r, g, b;

    tmp = ft_strdup(s);
    if (!tmp)
        return (err("malloc"));
    p1 = tmp;
    p2 = tmp;
    while (*p2 && *p2 != ',')
        p2++;
    if (!*p2)
        return (free(tmp), err("bad color"));
    *p2++ = '\0';
    if (parse_one(p1, &r))
        return (free(tmp), err("bad r"));
    p1 = p2;
    while (*p2 && *p2 != ',')
        p2++;
    if (!*p2)
		return (free(tmp), err("bad color"));
	*p2++ = '\0';
	if (parse_one(p1, &g))
		return (free(tmp), err("bad g"));
	if (parse_one(p2, &b))
		return (free(tmp), err("bad b"));
	free(tmp);
	*out_color = (r << 16) | (g << 8) | b;
	return (0);
}