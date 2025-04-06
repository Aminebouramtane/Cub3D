/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:40:07 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 11:06:01 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	get_x(t_init *vars, int ray, double *x)
{
	*x = get_x_render(vars, ray);
	if (is_animation(vars, ray))
		*x = get_x_render(vars, ray);
	else if (is_door(vars, ray))
		*x = get_x_render(vars, ray);
}

void	animation(t_init *vars)
{
	int	frame;

	frame = vars->animation->frame;
	if (frame < 5)
	{
		vars->animation->index = 0;
		(vars->animation->frame)++;
	}
	else if (frame < 10)
	{
		vars->animation->index = 1;
		(vars->animation->frame)++;
	}
	else if (frame < 15)
	{
		vars->animation->index = 2;
		(vars->animation->frame)++;
	}
	else
		vars->animation->frame = 0;
}

void	draw_animation(t_init *vars, double *x, int ray)
{
	if (vars->rays[ray].ray_side == 1)
		*x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_y,
						vars->tile_size)) / vars->tile_size)
			* vars->animation->width[vars->animation->index];
	else if (vars->rays[ray].ray_side == 2)
		*x = ((fmod(vars->rays[ray].ray_y, vars->tile_size)) / vars->tile_size)
			* vars->animation->width[vars->animation->index];
	else if (vars->rays[ray].ray_side == 3)
		*x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_x,
						vars->tile_size)) / vars->tile_size)
			* vars->animation->width[vars->animation->index];
	else if (vars->rays[ray].ray_side == 4)
		*x = ((fmod(vars->rays[ray].ray_x, vars->tile_size)) / vars->tile_size)
			* vars->animation->width[vars->animation->index];
}

int	is_animation(t_init *vars, int ray)
{
	int		map_g_i_x;
	int		map_g_i_y;
	char	map_cell;

	map_g_i_x = floor(vars->rays[ray].ray_x / vars->tile_size);
	map_g_i_y = floor(vars->rays[ray].ray_y / vars->tile_size);
	map_cell = vars->map[map_g_i_y][map_g_i_x];
	if (map_cell == 'A')
	{
		vars->animation->is_display = 1;
		return (1);
	}
	return (0);
}
