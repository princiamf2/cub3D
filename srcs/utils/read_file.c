/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:48:11 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 14:09:52 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char *read_all(int fd)
{
    char buf[1024];
    char *res;
    char *tmp;
    ssize_t r;
    size_t oldlen;
    ssize_t j;
    size_t i;

    res = NULL;
    while ((r = read(fd, buf, sizeof(buf))) > 0)
    {
        if (res)
            oldlen = ft_strlen(res);
        else
            oldlen = 0;
        tmp = malloc(oldlen + r + 1);
        if (!tmp)
            return (free(res), NULL);
        i = 0;
        while (i < oldlen)
        {
            tmp[i] = res[i];
            i++;
        }
        j = 0;
        while (j < r)
        {
            tmp[oldlen + j] = buf[j];
            j++;
        }
        tmp[oldlen + r] = '\0';
        free(res);
        res = tmp;
    }
    return (res);
}

char    **split_lines_from_fd(int fd, int *out_count)
{
    char *all;
    char **lines;
    int count;
    int i;
    int j;
    int k;
    int x;
    
    all = read_all(fd);
    if (!all)
        return (NULL);
    count = 1;
    i = 0;
    while (all[i])
    {
        if (all[i++] == '\n')
            count++;
    }
    lines = malloc(sizeof(char *) * (count + 1));
    if (!lines)
        return (free(all), NULL);
    i = 0; k = 0;
    while (all[i])
    {
        j = i;
        while (all[i] && all[i] != '\n')
            i++;
        lines[k] = malloc(i - j + 1);
        if (!lines[k])
            return (free(all), free_lines(lines), NULL);
        x = 0;
        while (x < i - j)
        {
            lines[k][x] = all[j + x];
            x++;
        }
        lines[k][i - j] = '\0';
        k++;
        if (all[i] == '\n')
            i++;
    }
    lines[k] = NULL;
    if (out_count)
        *out_count = k;
    free(all);
    return (lines);
}

void    free_lines(char **lines)
{
    int i;
    
    if (!lines)
        return;
    i = 0;
    while (lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}

int err(const char *msg)
{
    write(2, "Error\n", 6);
    if (msg)
    {
        while (*msg)
            write(2, msg++, 1);
        write(2, "\n", 1);
    }
    return (1);
}