/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:49:53 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 15:25:50 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "../includes/libft/libft.h"
# include "mlx.h"
# include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define UP_AROW 65362
# define DOWN_AROW 65364
# define RIGHT_AROW 65363
# define LEFT_AROW 65361

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction_u_d;
	int		walk_direction_l_r;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}	t_player;

typedef struct s_rays
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	double	distance;
	double	wall_h;
	double	b_pix;
	double	t_pix;
	int		side;
	int		ray_side;
}	t_rays;

typedef struct s_data
{
	int		nb_of_rows;
	int		nb_of_colums;
	int		width;
	int		height;
	char	**map_structure_clone;
	char	**map_structure;
	char	**full_map_data;
	char	*texture_north;
	char	*texture_south;
	char	*texture_west;
	char	*texture_east;
	char	*texture_color;
	char	*texture_fcolor;
	int		ceiling_color;
	int		floor_color;
	int		counters[6];
	int		player_x;
	int		player_y;
}	t_data;

typedef struct s_init
{
	void		*mlx;
	void		*win;
	char		**map;
	void		*mlx_img;
	char		*data_img;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			window_width;
	int			window_height;
	int			prgrm_runing;
	int			tile_size;
	int			map_rows_num;
	int			map_cols_num;
	float		fov_angle;
	size_t		num_rays;
	t_player	*player;
	t_rays		*rays;
	int			color_floor;
	int			color_ceiling;
	t_data		*data;
	void		*textures[4];
	char		*texture_data[4];
	int			texture_width[4];
	int			texture_height[4];
	int			texture_bpp[4];
	int			texture_line_size[4];
	int			texture_endian[4];
	int			color;
}	t_init;

typedef struct s_dda
{
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
}	t_dda;

char		*get_next_line(int fd);
char		*ft_strjoin_next(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*read_all(int fd, char *last);
void		ft_free(char **str);
void		parsing_part(char *av[], t_data *data);
void		parse_map_file(char *name, t_data *data);
void		valid_map(char *name, t_data *data);
void		check_map(t_data *data);
void		get_color(t_data *data);
void		get_map(t_data *data, int i);
void		get_texture_config(t_data *data);
void		validate_texture_path(t_data *data);
void		textures_extension(t_data *data, char *texture);
void		check_identifiers(t_data *data, char *line);
int			is_identifier(t_data *data, char *line, int *values);
void		skip_space(char **line);
char		**my_split(char const *s, char c);
void		print_error(t_data *data, char *msg);
int			in_array(char to_search, char *search_in);
void		raycasting(t_data *data);
int			is_withspace(int c);
void		only_valid_characters(t_data *data, char *texture, char c);
void		valid_comma(t_data *data, char *texture);
void		is_valid_color(t_data *data, char *texture, char c);
long long	my_atoi(t_data *data, char *str);
void		print_repeated(t_data *data, int i);
void		parsing_map(t_data *data);
void		adjust_map_width(t_data *data);
void		ft_print(t_data *data, char **test);
int			get_position_x(char **map);
int			get_position_y(char **map);
size_t		ft_height(t_data *data);
size_t		ft_max_width(t_data *data);
void		init_player(t_init *vars);
void		handle_keys(t_init *vars);
size_t		ft_height(t_data *data);
size_t		ft_max_width(t_data *data);
void		cast_rays(t_init *vars);
int			ft_move_player(t_init *vars);
void		render_wall(t_init *vars, int ray);
int			map_h_wall(float x, float y, t_init *vars);
void		draw_floor_ceiling(t_init *vars, int ray, int t_pix, int b_pix);
void		put_one_pixel(t_init *vars, int x, int y, int color);
void		initialize_ray(t_init *vars, size_t i, float ray_angle);
void		perform_dda(t_init *vars, size_t i);
void		calc_np_position(t_init *vars, double *newPlayerX, \
			double *newPlayerY);
void		free_resources(t_init *vars);
void		ft_init_window(t_init *vars, t_data *pars);

#endif
