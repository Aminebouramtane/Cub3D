/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:43:52 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 11:43:45 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

float	calculate_delta_dist_x(float ray_angle)
{
	if (cos(ray_angle) == 0)
		return (INFINITY);
	else
		return (fabs(1 / cos(ray_angle)));
}

float	calculate_delta_dist_y(float ray_angle)
{
	if (sin(ray_angle) == 0)
		return (INFINITY);
	else
		return (fabs(1 / sin(ray_angle)));
}

void	initialize_step_and_side_dist(t_init *vars, size_t i, t_dda *dda)
{
	if (cos(vars->rays[i].ray_angle) < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (vars->rays[i].ray_x
				- floor(vars->rays[i].ray_x)) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (ceil(vars->rays[i].ray_x)
				- vars->rays[i].ray_x) * dda->delta_dist_x;
	}
	if (sin(vars->rays[i].ray_angle) < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (vars->rays[i].ray_y
				- floor(vars->rays[i].ray_y)) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (ceil(vars->rays[i].ray_y)
				- vars->rays[i].ray_y) * dda->delta_dist_y;
	}
}

int	check_step(int step_x, int side1, int side2)
{
	if (step_x == 1)
		return (side1);
	return (side2);
}

void	perform_dda(t_init *vars, size_t i)
{
	t_dda	dda;

	dda.delta_dist_x = calculate_delta_dist_x(vars->rays[i].ray_angle);
	dda.delta_dist_y = calculate_delta_dist_y(vars->rays[i].ray_angle);
	initialize_step_and_side_dist(vars, i, &dda);
	while (!map_h_wall(vars->rays[i].ray_x, vars->rays[i].ray_y, vars))
	{
		if (dda.side_dist_x < dda.side_dist_y)
		{
			dda.side_dist_x += dda.delta_dist_x;
			vars->rays[i].ray_x += dda.step_x * 0.1;
			vars->rays[i].ray_side = check_step(dda.step_x, 2, 1);
		}
		else
		{
			dda.side_dist_y += dda.delta_dist_y;
			vars->rays[i].ray_y += dda.step_y * 0.1;
			vars->rays[i].ray_side = check_step(dda.step_y, 3, 4);
		}
	}
}
