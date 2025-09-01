/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 23:47:22 by michel            #+#    #+#             */
/*   Updated: 2025/08/22 00:07:02 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int parse_one(char **s, int *out)
{
    int i;
    int v;
    
    i = 0;
    while ((*s)[i] == ' ')
        i++;
    if (!ft_isdigit((*s)[i]))
        return (1);
    v = 0;
    while (ft_isdigit((*s)[i]))
    {
        v = v * 10 + ((*s)[i] - '0');
        i++;
    }
    *out = v;
    *s += i;
    return (0);
}

int parse_rgb(char *s, t_rgb *out)
{
    int r;
    int g;
    int b;
    
    if (parse_one(&s, &r))
        return (err("bad rgb"));
    if (*s++ != ',')
        return (err("bad rgb"));
    if (parse_one(&s, &g))
        return (err("bad rgb"));
    if (*s++ != ',')
        return (err("bad rgb"));
    if (parse_one(&s, &b))
        return (err("bad rgb"));
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (err("rgb out of range"));
    out->r = r;
    out->g = g;
    out->b = b;
    out->packed = pack_rgb(r, g, b);
    return (0);
}