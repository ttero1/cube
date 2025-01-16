/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:50 by ttero             #+#    #+#             */
/*   Updated: 2025/01/16 19:40:06 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define WIDTH 800
# define HEIGHT 800
# define SPEED 0.8
# define SPEED_RAD 0.05
# define BLOCK_SIZE 30
#define PI 3.141592653589793


typedef struct s_raycast
{
	double	distance;
	double x_pos_ray;
	double y_pos_ray;
	int		hit_wall;
}				t_raycast;


typedef struct s_data
{
	mlx_t		*mlx;
	double		x_pos;
	double		y_pos;
	double		angle;
	int			map_size_y;
	int			map_size_x;

	mlx_image_t	*image;
}				t_data;


#endif
