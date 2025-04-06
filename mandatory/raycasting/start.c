/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:33 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 15:25:16 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	initialize_window_and_image(t_init *vars, t_data *pars)
{
	vars->tile_size = 30;
	ft_init_window(vars, pars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (0);
	vars->win = mlx_new_window(vars->mlx, \
		vars->window_width, vars->window_height, "cub3D");
	if (!vars->win)
		return (0);
	vars->mlx_img = mlx_new_image(vars->mlx, \
		vars->window_width, vars->window_height);
	if (!vars->mlx_img)
		return (0);
	vars->data_img = mlx_get_data_addr(vars->mlx_img, \
		&vars->bits_per_pixel, &vars->size_line, &vars->endian);
	vars->map = pars->map_structure;
	vars->map_rows_num = ft_height(pars);
	vars->map_cols_num = ft_max_width(pars);
	vars->num_rays = vars->window_width;
	vars->fov_angle = (60 * (M_PI / 180));
	return (1);
}

void	initialize_textures(t_init *vars)
{
	vars->textures[0] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_west, \
		&vars->texture_width[0], &vars->texture_height[0]);
	vars->textures[1] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_north, \
		&vars->texture_width[1], &vars->texture_height[1]);
	vars->textures[2] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_east, \
		&vars->texture_width[2], &vars->texture_height[2]);
	vars->textures[3] = mlx_xpm_file_to_image(vars->mlx, \
		vars->data->texture_south, \
		&vars->texture_width[3], &vars->texture_height[3]);
}

int	initialize_game_variables(t_init *vars)
{
	int		i;

	vars->num_rays = vars->window_width;
	initialize_textures(vars);
	i = 0;
	while (i < 4)
	{
		if (!vars->textures[i])
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("Unable to Load Textures", 2);
			free_resources(vars);
		}
		vars->texture_data[i] = mlx_get_data_addr(vars->textures[i],
				&vars->texture_bpp[i], &vars->texture_line_size[i],
				&vars->texture_endian[i]);
		i++;
	}
	vars->rays = malloc(sizeof(t_rays) * vars->num_rays);
	if (!vars->rays)
		return (0);
	return (1);
}

int	init_values(t_init *vars, t_data *pars)
{
	vars->rays = NULL;
	if (!initialize_window_and_image(vars, pars))
		return (0);
	if (!initialize_game_variables(vars))
		return (0);
	return (1);
}

void	raycasting(t_data *data)
{
	t_init		vars;
	t_player	player;

	vars.data = data;
	vars.player = &player;
	init_values(&vars, data);
	init_player(&vars);
	handle_keys(&vars);
	mlx_loop_hook(vars.mlx, ft_move_player, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
}
