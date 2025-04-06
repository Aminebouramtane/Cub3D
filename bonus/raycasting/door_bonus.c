/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:50:52 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 11:04:41 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	is_door(t_init *vars, int ray)
{
	int		map_g_i_x;
	int		map_g_i_y;
	char	map_cell;

	map_g_i_x = floor(vars->rays[ray].ray_x / vars->tile_size);
	map_g_i_y = floor(vars->rays[ray].ray_y / vars->tile_size);
	map_cell = vars->map[map_g_i_y][map_g_i_x];
	if (map_cell == 'D')
	{
		vars->is_door = 1;
		return (1);
	}
	return (0);
}

void	draw_door(t_init *vars, double *x, int ray)
{
	if (vars->rays[ray].ray_side == 1)
		*x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_y,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[4];
	else if (vars->rays[ray].ray_side == 2)
		*x = ((fmod(vars->rays[ray].ray_y, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[4];
	else if (vars->rays[ray].ray_side == 3)
		*x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_x,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[4];
	else if (vars->rays[ray].ray_side == 4)
		*x = ((fmod(vars->rays[ray].ray_x, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[4];
}

void	handle_door(t_init *vars, int x, int y)
{
	if (vars->data->map_structure[x][y] == 'D')
		vars->data->map_structure[x][y] = 'd';
	else if (vars->data->map_structure[x][y] == 'd')
		vars->data->map_structure[x][y] = 'D';
}

void	open_door(t_init *vars)
{
	int	x;
	int	y;

	x = floor(vars->player->player_y / vars->tile_size);
	y = floor(vars->player->player_x / vars->tile_size);
	if (in_array(vars->data->map_structure[x][y - 1], "Dd"))
		handle_door(vars, x, y - 1);
	else if (in_array(vars->data->map_structure[x][y + 1], "Dd"))
		handle_door(vars, x, y + 1);
	else if (in_array(vars->data->map_structure[x - 1][y], "Dd"))
		handle_door(vars, x - 1, y);
	else if (in_array(vars->data->map_structure[x + 1][y], "Dd"))
		handle_door(vars, x + 1, y);
}
