/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:56:31 by michel            #+#    #+#             */
/*   Updated: 2025/11/17 14:05:39 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char    *ft_strtrim_spaces(char *s)
{
    int start;
    int end;
    int len;
    char *out;
    int i;

    if (!s)
        return (NULL);
    start = 0;
    while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n'
        || s[start] == '\r' || s[start] == '\v' || s[start] == '\f')
        start++;
    end = ft_strlen(s);
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'
            || s[end -1] == '\n' || s[end - 1] == '\r'
            || s[end - 1] == '\v' || s[end - 1] == '\f'))
        end--;
    len = end - start;
    out = malloc(len + 1);
    if (!out)
        return (NULL);
    i = 0;
    while (i < len)
    {
        out[i] = s[start + i];
        i++;
    }
    out[i] = '\0';
    return (out);
}

int ft_atoi_strict(const char *s, int *ok)
{
    long    res;
    int     sign;
    int     i;

    if (!s || !ok)
        return (0);
    *ok = 1;
    i = 0;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
            || s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
        i++;
    sign = 1;
    if (s[i] == '-' || s[i] == '+')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    if (s[i] < '0' || s[i] > '9')
        return (*ok = 0, 0);
    res = 0;
    while (s[i] >= '0' && s[i] <= '9')
    {
        res = res * 10 + (s[i] - '0');
        if (res * sign > INT_MAX || res * sign < INT_MIN)
            return (*ok = 0, 0);
        i++;
    }
    if (s[i] != '\0')
        return (*ok = 0, 0);
    return ((int)(res * sign));
}