#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 800
# define SPEED 0.8
# define SPEED_RAD 0.05
# define BLOCK_SIZE 30
# define PI 3.141592653589793
# define RAD 0.01745329251



typedef enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}					t_wall;

typedef struct s_texture
{
    double      texture_step;
    double      texture_pos;
    mlx_image_t *texture;
    int         texture_x;
} t_texture;





typedef struct s_raycast
{
	double	distance;
	double x_pos_ray;
	double y_pos_ray;
	int		hit_wall;
	double	ray_dir_y;
	double	ray_dir_x;
}				t_raycast;




typedef struct	s_map
{
	char	**points;
	int		width;
	int		height;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	int		*floor_color;
	int		*ceiling_color;
}	t_map;

typedef struct	s_player
{
	int		x;
	int		y;
	char	player_pos;
}	t_player;

typedef struct	s_game
{
	t_map	map;
	t_player	player;
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_t		*mlx;
	double		x_pos;
	double		y_pos;
	double		angle;
	int			map_size_y;
	int			map_size_x;
	double 		distance;
	int32_t		mouse_x;
	t_raycast   *raycast;

	mlx_texture_t	*north_wall;
	mlx_texture_t	*west_wall;
	mlx_texture_t	*east_wall;
	mlx_texture_t	*south_wall;
	mlx_image_t		*north_wall_img;
	mlx_image_t		*south_wall_img;
	mlx_image_t		*west_wall_img;
	mlx_image_t		*east_wall_img;

	mlx_image_t	*image;
}	t_game;

/* main.c */
void	error(char *error_message);
void	print_game_state(t_game *game);
int		check_cub_file(const char *file);
void	free_map(t_game *game);
int		init_values(t_game *game);

/* parse_map.c */
int		search_char(char *s, int c);
int		check_valid_char(char *line);
int		validate_player_position(t_game *game);
int		check_png_file(char *file);
int		no_text(char *line, t_game *game);
int		so_text(char *line, t_game *game);
int		we_text(char *line, t_game *game);
int		ea_text(char *line, t_game *game);
int		floor_color(char *line, t_game *game);
int		ceiling_color(char *line, t_game *game);
int		parse_element(char *line, t_game *game);
void	free_rgb(char **rgb);
int		parse_color(char *line, int *color);
int		validate_row_edges(char *row, int row_index);
int		validate_row_spaces(char **map, int y, int x, t_game *game);
int		validate_top_and_bottom(char **map, t_game *game);
int		validate_map(t_game *game);
void	trim_newline(char *line);
int		save_line(char *line, t_game *game, int row);
int		count_map_rows(const char *file);
int		init_map(const char *file, t_game *game);
int		process_content(char *line, t_game *game, int *row, int *map);
int		process_map(char *line, t_game *game, int fd, int *row);
int		finalize_map(t_game *game, int row);
int		parse_map(const char *file, t_game *game);




int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void paint_block(t_game *game, int x, int y, int flag);
void draw_player(t_game *game);
void draw_map(t_game *game);
int check_wall(t_game *game);
int check_wall_reverse(t_game *game);
int check_wall_right(t_game *game);
int check_wall_left(t_game *game);
double calc_y_distance(t_game *game);
double calc_x_distance(t_game *game);
double calc_down(t_game *game);
double calc_left(t_game *game);
bool check_wall2(int x, int y, t_game *game);
double calc_y_distance2(t_game *game, t_raycast *raycast, double angle);
double calc_x_distance2(t_game *game, t_raycast *raycast, double angle);
void cast_rays(t_game *game, t_raycast *raycast, double angle);
t_raycast calc_distance(t_game *game, double angle);

void draw_ceiling(t_game *game, int start, int x);
void draw_floor(t_game *game, int end, int x);
void draw_view(t_game *game, double distances[60]);
void ft_hook(void *param);
void load_texture(t_game *game);


#endif
