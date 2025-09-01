/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_spritesheet.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michel <michel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 13:47:35 by michel            #+#    #+#             */
/*   Updated: 2025/09/01 17:39:49 by michel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int load_sprite(t_game *g, t_sprite *s, const char *path, int frames, int rows)
{
    int w;
    int h;

    ft_bzero((s), sizeof(*s));
    s->img = mlx_xpm_file_to_image(g->mlx, (char *)path, &w, &h);
    if (!s->img)
        return (err("failed to load sprite\n"));
    s->addr = mlx_get_data_addr(s->img, &s->bpp, &s->line_len, &s->endian);
    s->w = w;
    s->h = h;
    if (frames <= 0)
        s->frames_total = 1;
    else
        s->frames_total = frames;
    if (rows <= 0)
        s->rows_total = 1;
    else
        s->rows_total= rows;
    if (s->w % s->frames_total != 0)
        return (err("sprite width not divisible by frames"));
    if (s->h % s->rows_total != 0)
        return (err("sprite heigth not divisible by rows"));
    s->frame_w = s->w / s->frames_total;
    s->row_h = s->h / s->rows_total;
    s->cur = 0;
    s->row = 0;
    s->last_ms = now_ms();
    s->bgcol = *(int *)(s->addr + 0 * s->line_len + 0 * (s->bpp / 8));
    return (0);
}

void sprite_set_row(t_sprite *s, int row)
{
    if (!s)
        return;
    if (row < 0)
        row = 0;
    if (row >= s->rows_total)
        row = s->rows_total - 1;
    if (s->row != row)
    {
        s->row = row;
        s->cur = 0;
    }
}

void sprite_step(t_sprite *s, int ms_per_frame, int is_moving)
{
    long ms;
    
    if (!is_moving)
        return ;
    ms = now_ms();
    if (ms - s->last_ms >= (long)ms_per_frame)
    {
        s->cur++;
        if (s->cur >= s->frames_total)
            s->cur = 0;
        s->last_ms = ms;
    }
}

int enemy_row_from_camvel(double tvx, double tvy)
{
    const double eps = 1e-6;
    double ax;
    double ay;
    
    ax = dabsval(tvx);
    ay = dabsval(tvy);
    if (ax <= eps && ay <= eps)
        return (0);
    if (ay >= ax)
    {
        if (tvy > 0.0)
            return (0);
        else
            return (1);
    }
    if (tvx < 0.0)
        return (3);
    else
        return (2);
}