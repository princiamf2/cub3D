/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:47:03 by michel            #+#    #+#             */
/*   Updated: 2025/08/25 13:03:40 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_isspace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

char *read_all(char *path)
{
    int fd;
    int r;
    char *buf;
    char tmp[4096];
    int cap;
    int len;
    char *nbuf;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    buf = NULL;
    cap = 0;
    len = 0;
    r = read(fd, tmp, sizeof(tmp));
    while (r > 0)
    {
        if (len + r + 1 > cap)
        {
            if (cap)
                cap = cap * 2;
            else
                cap = 8192;
            while (cap < len + r + 1)
                cap *= 2;
            nbuf = (char *)malloc(cap);
            if (!nbuf)
                return (close(fd), free(buf), NULL);
            if (buf)
                ft_memcpy(nbuf, buf, len);
            free(buf);
            buf = nbuf;
        }
        ft_memcpy(buf + len, tmp, r);
        len += r;
        r = read(fd, tmp, sizeof(tmp));
    }
    close(fd);
    if (!buf)
        return (NULL);
    buf[len] = '\0';
    return (buf);
}

char **split_lines_keep(char *buf, int *n)
{
    int i;
    int k;
    int cnt;
    char **v;
    
    i = 0;
    cnt = 1;
    while (buf[i])
    {
        if (buf[i++] == '\n')
            cnt++;
    }
    v = (char **)ft_calloc(cnt + 1, sizeof(char *));
    if (!v)
        return (NULL);
    i = 0;
    k = 0;
    v[k++] = buf;
    while (buf[i])
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            v[k++] = &buf[i + 1];
        }
        i++;
    }
    *n = k;
    return (v);
}

char *trim_inplace(char *s)
{
    int i;
    int j;
    
    i = 0;
    j = (int)ft_strlen(s) - 1;
    while (s[i] && ft_isspace(s[i]))
        i++;
    while (j >= i && ft_isspace(s[j]))
        j--;
    s[j + 1] = '\0';
    return (s + i);
}

int pack_rgb(int r, int g, int b)
{
    return ((r & 255) << 16) | ((g & 255) << 8) | (b & 255);
}