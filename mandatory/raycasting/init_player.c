/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:19 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 17:44:20 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	ft_rotate_angle(int player_x, int player_y, t_init *vars)
{
	if (vars->map[player_y][player_x] == 'N')
		return (M_PI / 2);
	else if (vars->map[player_y][player_x] == 'E')
		return (0);
	else if (vars->map[player_y][player_x] == 'S')
		return ((3 * M_PI) / 2);
	else if (vars->map[player_y][player_x] == 'W')
		return (M_PI);
	else
		return (-1);
}

void	init_player(t_init *vars)
{
	int	player_y;
	int	player_x;

	player_y = get_position_y(vars->map);
	player_x = get_position_x(vars->map);
	if (player_x == -1 || player_y == -1)
	{
		ft_putendl_fd("Error\n: Player position not found in the map.\n", 2);
		free_resources(vars);
		exit(1);
	}
	vars->player->player_x = (player_x * vars->tile_size);
	vars->player->player_y = (player_y * vars->tile_size);
	vars->player->width = 5;
	vars->player->height = 5;
	vars->player->turn_direction = 0;
	vars->player->walk_direction_u_d = 0;
	vars->player->walk_direction_l_r = 0;
	vars->player->rotation_angle = ft_rotate_angle(player_x, player_y, vars);
	vars->player->walk_speed = 4;
	vars->player->turn_speed = 4 * (M_PI / 180);
}
