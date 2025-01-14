/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:14:50 by ttero             #+#    #+#             */
/*   Updated: 2025/01/14 10:22:28 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

# define WIDTH 400
# define HEIGHT 400
# define SPEED 0.2
# define SPEED_RAD 0.02
#define PI 3.141592653589793


typedef struct s_data
{
	mlx_t		*mlx;
	double		x_pos;
	double		y_pos;
	double		angle;

	mlx_image_t	*image;
}				t_data;


#endif
