/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttero <ttero@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:27:15 by mjaakkol          #+#    #+#             */
/*   Updated: 2025/01/29 15:47:16 by ttero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_mlx(mlx_t *mlx, t_game *game)
{
	if (!mlx)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx;
	game->image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!game->image)
	{
		mlx_terminate(game->mlx);
		free_map(game);
		error("Error\nFailed to init image");
	}
	return ;
}

int	initialize_mlx(t_game *game)
{
	start_mlx(mlx_init(WIDTH, HEIGHT, "Cube", true), game);
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		free_map(game);
		error("Error\nFailed to create image");
		return (0);
	}
	return (1);
}

int	parse_and_load_map(char *filename, t_game *game)
{
	printf("Loading map: %s\n", filename);
	if (!parse_map(filename, game))
	{
		free_map(game);
		error("Error\nFile not valid or failure in parsing");
	}
	return (1);
}

void	free_textures(t_game *game)
{
	mlx_delete_texture(game->north_wall);
	mlx_delete_texture(game->south_wall);
	mlx_delete_texture(game->east_wall);
	mlx_delete_texture(game->west_wall);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error("Error\nUsage: ./cub3D <filename.cub>");
	if (check_cub_file(argv[1]) == 0)
		error("Error\nInvalid file format");
	if (!init_values(&game))
		error("Error\nFailed to initialize values");
	parse_and_load_map(argv[1], &game);
	initialize_mlx(&game);
	load_texture(&game);
	get_map_size(&game);
	get_player_position(&game);
	printf("Map loaded succesfully!\n");
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	mlx_close_window(game.mlx);
	free_textures(&game);
	mlx_terminate(game.mlx);
	free_map(&game);
	printf("Map closed!\n");
	return (EXIT_SUCCESS);
}
