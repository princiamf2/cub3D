/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:32:23 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 13:01:32 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int err(char *msg)
{
    write(2, "Error\n", 6);
    if (msg)
        write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (1);
}

void *xfree(void *p)
{
    if (p)
        free(p);
    return (NULL);
}

void    free_split(char **v)
{
    if (!v)
        return ;
    free(v);
}