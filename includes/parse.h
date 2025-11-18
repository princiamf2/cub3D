#ifndef PARSE_H
# define PARSE_H
# include "cub3d.h"


/* parse_elements.c */
int		parse_elements(t_game *g, char **lines, int *i);

/* parse_colors.c */
int		parse_color_line(const char *s, int *out_color);

/* parse_map.c */
int		parse_map(t_game *g, char **lines, int start);

/* map_rectify.c */
int		rectify_map(t_map *map);

/* map_check.c */
int		check_map_closed(t_map *map, t_player *p);

#endif
