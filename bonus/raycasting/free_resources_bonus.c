/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:05 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 10:39:39 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	free_resources_helper(t_init *vars)
{
	if (vars->mlx && vars->win)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
	}
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->data)
	{
		ft_free(vars->data->full_map_data);
		ft_free(vars->data->map_structure);
		ft_free(vars->data->map_structure_clone);
	}
	(free(vars->rays), free(vars->mlx), exit(0));
}

void	free_resources(t_init *vars)
{
	int	i;	

	i = 0;
	if (vars->mlx && vars->mlx_img)
		mlx_destroy_image(vars->mlx, vars->mlx_img);
	while (i < 5)
	{
		if (i < 3 && vars && vars->animation && vars->animation->textures[i])
			mlx_destroy_image(vars->mlx, vars->animation->textures[i]);
		if (vars->textures[i])
			mlx_destroy_image(vars->mlx, vars->textures[i]);
		i++;
	}
	free_resources_helper(vars);
}
