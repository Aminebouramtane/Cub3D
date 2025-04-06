/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_resources.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:47:09 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 11:16:40 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

void initialize_textures(t_init *vars)
{
    vars->textures[0] = mlx_xpm_file_to_image(vars->mlx, 
        vars->data->texture_west, 
        &vars->texture_width[0], &vars->texture_height[0]);
    vars->textures[1] = mlx_xpm_file_to_image(vars->mlx, 
        vars->data->texture_north, 
        &vars->texture_width[1], &vars->texture_height[1]);
    vars->textures[2] = mlx_xpm_file_to_image(vars->mlx, 
        vars->data->texture_east, 
        &vars->texture_width[2], &vars->texture_height[2]);
    vars->textures[3] = mlx_xpm_file_to_image(vars->mlx, 
        vars->data->texture_south, 
        &vars->texture_width[3], &vars->texture_height[3]);
    vars->textures[4] = mlx_xpm_file_to_image(vars->mlx, 
        "textures/close.xpm", 
        &vars->texture_width[4], &vars->texture_height[4]);

    // Load player texture (gun in hand) - pis-0.xpm
    vars->textures[5] = mlx_xpm_file_to_image(vars->mlx, 
        "textures/pis-0.xpm", 
        &vars->texture_width[5], &vars->texture_height[5]);

    if (!vars->textures[5])
    {
        printf("Error: Failed to load player texture (pis-0.xpm)\n");
        exit(1);
    }

    // Load animation textures
    vars->animation->textures[0] = mlx_xpm_file_to_image(vars->mlx, 
        "textures/animation/1.xpm", 
        &vars->animation->width[0], &vars->animation->height[0]);
    vars->animation->textures[1] = mlx_xpm_file_to_image(vars->mlx, 
        "textures/animation/2.xpm", 
        &vars->animation->width[1], &vars->animation->height[1]);
    vars->animation->textures[2] = mlx_xpm_file_to_image(vars->mlx, 
        "textures/animation/3.xpm", 
        &vars->animation->width[2], &vars->animation->height[2]);
}

void	initialize_helper(t_init *vars)
{
	vars->animation->frame = 0;
	vars->animation->index = 0;
	vars->animation->is_display = 0;
	vars->is_door = 0;
	vars->num_rays = vars->window_width;
	initialize_textures(vars);
}

void	initialize_animation(t_init *vars, int i)
{
	if (!vars->animation->textures[i])
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Unable to Load Textures", 2);
		free_resources(vars);
	}
	vars->animation->data[i] = mlx_get_data_addr(vars->\
	animation->textures[i], &vars->animation->bpp[i], \
	&vars->animation->line_size[i], &vars->animation->endian[i]);
}

int	initialize_game_variables(t_init *vars)
{
	int		i;

	initialize_helper(vars);
	i = 0;
	while (i < 6)
	{
		if (i < 3)
			initialize_animation(vars, i);
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
