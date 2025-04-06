/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:38 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 11:39:06 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	put_one_pixel(t_init *vars, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= vars->window_width || y < 0 || y >= vars->window_height)
		return ;
	offset = (y * vars->size_line) + (x * (vars->bits_per_pixel / 8));
	*(unsigned int *)(vars->data_img + offset) = color;
}

static double	get_x_render(t_init *vars, int ray)
{
	double	x;

	x = 0;
	if (vars->rays[ray].ray_side == 1)
		x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_y,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[0];
	else if (vars->rays[ray].ray_side == 2)
		x = ((fmod(vars->rays[ray].ray_y, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[2];
	else if (vars->rays[ray].ray_side == 3)
		x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_x,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[1];
	else if (vars->rays[ray].ray_side == 4)
		x = ((fmod(vars->rays[ray].ray_x, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[3];
	return (x);
}

static unsigned int	my_get_color(t_init *vars, int x, int y, int index)
{
	int				offset;
	unsigned int	color;

	if (x < 0 || x > vars->texture_width[index]
		|| y < 0 || y > vars->texture_height[index])
		return (0);
	offset = (y * vars->texture_line_size[index])
		+ (x * (vars->texture_bpp[index] / 8));
	color = *(unsigned int *)(vars->texture_data[index] + offset);
	return (color);
}

static double	get_y_render(t_init *vars, double n, int ray)
{
	double	y;

	y = 0;
	if (vars->rays[ray].ray_side == 1)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[0];
	else if (vars->rays[ray].ray_side == 2)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[2];
	else if (vars->rays[ray].ray_side == 3)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[1];
	else if (vars->rays[ray].ray_side == 4)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[3];
	return (y);
}

void	render_wall(t_init *vars, int ray)
{
	unsigned int	color;
	double			x;
	int				i;
	double			n;

	draw_floor_ceiling(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
	x = get_x_render(vars, ray);
	i = vars->rays[ray].t_pix;
	while (i < vars->rays[ray].b_pix)
	{
		n = (i - vars->rays[ray].t_pix);
		if (vars->rays[ray].wall_h >= vars->window_height)
			n += (vars->rays[ray].wall_h - vars->window_height) / 2;
		if (vars->rays[ray].ray_side == 1)
			color = my_get_color(vars, x, get_y_render(vars, n, ray), 0);
		else if (vars->rays[ray].ray_side == 2)
			color = my_get_color(vars, x, get_y_render(vars, n, ray), 2);
		else if (vars->rays[ray].ray_side == 3)
			color = my_get_color(vars, x, get_y_render(vars, n, ray), 1);
		else if (vars->rays[ray].ray_side == 4)
			color = my_get_color(vars, x, get_y_render(vars, n, ray), 3);
		put_one_pixel(vars, ray, i, color);
		i++;
	}
}
