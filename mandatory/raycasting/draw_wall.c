/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:02 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 11:53:17 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_floor_ceiling(t_init *vars, int ray, int t_pix, int b_pix)
{
	int		i;

	i = 0;
	while (i < t_pix)
		put_one_pixel(vars, ray, i++, vars->data->ceiling_color);
	i = b_pix;
	while (i < (int)vars->window_height)
		put_one_pixel(vars, ray, i++, vars->data->floor_color);
}

int	map_h_wall(float x, float y, t_init *vars)
{
	int	map_g_i_x;
	int	map_g_i_y;

	if (x < 0 || x >= vars->window_width || y < 0 || y >= vars->window_height)
	{
		return (1);
	}
	map_g_i_x = round(x / vars->tile_size);
	map_g_i_y = round(y / vars->tile_size);
	return (vars->map[map_g_i_y][map_g_i_x] == '1');
}
