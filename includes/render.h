#ifndef RENDER_H
# define RENDER_H
# include "cub3d.h"

typedef struct s_ray {
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_x;
    double  wall_x;
}	t_ray;

void	render_frame(t_game *g);
void	raycast_column(t_game *g, int x);
void	draw_wall_stripe(t_game *g, int x, t_ray *r);

#endif
