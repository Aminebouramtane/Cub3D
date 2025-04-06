/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:33 by smarsi            #+#    #+#             */
/*   Updated: 2025/02/01 09:51:21 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	ft_init_window(t_init *vars, t_data *pars)
{
	vars->window_width = 1000;
	vars->window_height = 700;
	(void) pars;
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
	t_animation	animation;

	vars.animation = &animation;
	vars.data = data;
	vars.player = &player;
	init_values(&vars, data);
	init_player(&vars);
	handle_keys(&vars);
	mlx_loop_hook(vars.mlx, ft_move_player, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
}
