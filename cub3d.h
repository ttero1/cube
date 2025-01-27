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


typedef struct s_raycast
{
	double	distance;
	double x_pos_ray;
	double y_pos_ray;
	int		hit_wall;
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
	t_raycast   *raycast;

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
int		parse_element(char *line, t_game *game);
int		parse_color(char *line, int *color);
int		validate_map(t_game *game);
void	trim_newline(char *line);
int		save_line(char *line, t_game *game, int row);
int		count_map_rows(const char *file);
//int		init_map(t_map *map);
//void	init_player(t_player *player);
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



#endif
