/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:38 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 10:46:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	put_one_pixel(t_init *vars, int x, int y, int color)
{
	int	offset;

	if (x < 0 && x > vars->window_width && y < 0 && y > vars->window_height)
		return ;
	offset = (y * vars->size_line) + (x * (vars->bits_per_pixel / 8));
	*(unsigned int *)(vars->data_img + offset) = color;
}

double	get_x_render(t_init *vars, int ray)
{
	double	x;

	x = 0;
	if (vars->animation->is_display)
		draw_animation(vars, &x, ray);
	else if (vars->is_door)
		draw_door(vars, &x, ray);
	else if (vars->rays[ray].ray_side == 1)
		x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_y,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[0];
	else if (vars->rays[ray].ray_side == 2)
		x = ((fmod(vars->rays[ray].ray_y, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[1];
	else if (vars->rays[ray].ray_side == 3)
		x = (((double)vars->tile_size - fmod(vars->rays[ray].ray_x,
						vars->tile_size)) / vars->tile_size)
			* vars->texture_width[2];
	else if (vars->rays[ray].ray_side == 4)
		x = ((fmod(vars->rays[ray].ray_x, vars->tile_size)) / vars->tile_size)
			* vars->texture_width[3];
	return (x);
}

static double	get_y_render(t_init *vars, double n, int ray)
{
	double	y;

	y = 0;
	if (vars->animation->is_display)
		y = (n / (vars->rays[ray].wall_h))
			* vars->animation->height[vars->animation->index];
	else if (vars->is_door)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[4];
	else if (vars->rays[ray].ray_side == 1)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[0];
	else if (vars->rays[ray].ray_side == 2)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[2];
	else if (vars->rays[ray].ray_side == 3)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[1];
	else if (vars->rays[ray].ray_side == 4)
		y = (n / (vars->rays[ray].wall_h)) * vars->texture_height[3];
	return (y);
}

static unsigned int	get_ray_color(t_init *vars, double x, int ray, int n)
{
	unsigned int	color;

	color = 0;
	if (vars->is_door)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 4);
	else if (vars->animation->is_display)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 5);
	else if (vars->rays[ray].ray_side == 1)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 0);
	else if (vars->rays[ray].ray_side == 2)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 2);
	else if (vars->rays[ray].ray_side == 3)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 1);
	else if (vars->rays[ray].ray_side == 4)
		color = my_get_color(vars, x, get_y_render(vars, n, ray), 3);
	return (color);
}

void	render_wall(t_init *vars, int ray)
{
	unsigned int	color;
	int				i;

	double (x), (n);
	draw_floor_ceiling(vars, ray, vars->rays[ray].t_pix, vars->rays[ray].b_pix);
	get_x(vars, ray, &x);
	i = vars->rays[ray].t_pix;
	while (i < vars->rays[ray].b_pix)
	{
		n = (i - vars->rays[ray].t_pix);
		if (vars->rays[ray].wall_h >= vars->window_height)
			n += (vars->rays[ray].wall_h - vars->window_height) / 2;
		color = get_ray_color(vars, x, ray, n);
		put_one_pixel(vars, ray, i, color);
		i++;
	}
}
