/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:05 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 17:44:06 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_resources(t_init *vars)
{
	int	i;

	i = 0;
	if (vars->mlx_img)
		mlx_destroy_image(vars->mlx, vars->mlx_img);
	while (i < 4)
	{
		if (vars->textures[i])
			mlx_destroy_image(vars->mlx, vars->textures[i]);
		i++;
	}
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	ft_free(vars->data->full_map_data);
	ft_free(vars->data->map_structure);
	ft_free(vars->data->map_structure_clone);
	(free(vars->rays), free(vars->mlx), exit(0));
}
