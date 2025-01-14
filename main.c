/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:45:18 by ttero             #+#    #+#             */
/*   Updated: 2025/01/14 10:35:22 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


void	ft_hook(void *param)
{
	t_data	*data;

	data = param;
	//key_hooks2(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->x_pos += SPEED * cos(data->angle);
		data->y_pos += SPEED * sin(data->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->x_pos -= SPEED * cos(data->angle);
		data->y_pos -= SPEED * sin(data->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->angle -= SPEED_RAD;
		if (data->angle >= 2 * PI)
			data->angle +=  2 * PI;
		printf("%f\n", data->angle);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->angle += SPEED_RAD;
		if (data->angle <= 2 * PI)
			data->angle -=  2 * PI;
	}
	//fractal(data);
	uint32_t	color;

	color = ft_pixel(
			100,
			100,
			100,
			255
			);
	mlx_put_pixel(data->image, data->x_pos, data->y_pos, color);
}

void	init(int argc, char **argv, t_data *data)
{
	data->x_pos = 2;
	data->y_pos = 20;
	data->angle = 0;
}

void	start_mlx(mlx_t *mlx, t_data *data)
{
	if (!mlx)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx;
	data->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data->image)
		return ;
}


int32_t	main(int argc, char **argv)
{
	t_data	data;

	init(argc, argv, &data);
	start_mlx(mlx_init(WIDTH, HEIGHT, "Fractol", true), &data);
	/* if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	} */
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_loop_hook(data.mlx, ft_hook, &data);
	//printf("AAA");
	//mlx_scroll_hook(data.mlx, &my_scrollhook, &data);
	mlx_loop(data.mlx);
	mlx_close_window(data.mlx);
	// mlx_delete_image(data.mlx, data.image);
	mlx_terminate(data.mlx);
	return (0);
}

