/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:23 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 19:48:08 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"
#include <stdio.h>


unsigned int my_get_o_color(t_init *vars, int x, int y, int index)
{
    int offset;
    unsigned int color;

    // Ensure coordinates are within bounds
    if (index == 5)  // Gun texture (pis-0.xpm)
    {
        if (x < 0 || x >= vars->texture_width[5] ||
            y < 0 || y >= vars->texture_height[5])
            return (0xFF000000); // Fully transparent pixel

        offset = (y * vars->texture_line_size[5]) +
                 (x * (vars->texture_bpp[5] / 8));
        color = *(unsigned int *)(vars->texture_data[5] + offset);

        // Skip fully black pixels (assuming black is used as transparency)
        if ((color & 0xFFFFFF) == 0x000000)
            return (0xFF000000);  // Transparent pixel
    }
    else  // Regular textures (walls, animations, etc.)
    {
        if (x < 0 || x >= vars->texture_width[index] ||
            y < 0 || y >= vars->texture_height[index])
            return (0xFF000000); // Fully transparent pixel

        offset = (y * vars->texture_line_size[index]) +
                 (x * (vars->texture_bpp[index] / 8));
        color = *(unsigned int *)(vars->texture_data[index] + offset);
    }

    return color;  // Return the valid color
}


void put_one_o_pixel(t_init *vars, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= vars->window_width || y < 0 || y >= vars->window_height)
        return;

    // Calculate pixel position in the image buffer
    offset = (y * vars->size_line) + (x * (vars->bits_per_pixel / 8));

    // Only draw non-transparent pixels (assuming black is 0x000000)
    if (color != 0x000000FF && color != 0x000000) // Adjust based on color depth
        *(unsigned int *)(vars->data_img + offset) = color;
}


void render_player_texture(t_init *vars)
{
    int player_x = vars->window_width / 2 - vars->texture_width[5] / 2;
    int player_y = vars->window_height - vars->texture_height[5];
    // exit(1);
    int x, y;
    unsigned int color;

    for (y = 0; y < vars->texture_height[5]; y++)
    {
        for (x = 0; x < vars->texture_width[5]; x++)
        {
            color = my_get_o_color(vars, x, y, 5);

            if ((color & 0xFFFFFF) != 0x000000) 
                put_one_o_pixel(vars, player_x + x, player_y + y, color);
        }
    }
}



void	update_player_rotation(t_init *vars)
{
	vars->player->rotation_angle += vars->player->turn_direction \
		* vars->player->turn_speed;
}

int	is_collision(double newPlayerX, double newPlayerY, t_init *vars)
{
	double	padding;

	padding = 1.5;
	return (
		map_h_wall(newPlayerX - padding, newPlayerY - padding, vars)
		|| map_h_wall(newPlayerX + padding, newPlayerY - padding, vars)
		|| map_h_wall(newPlayerX - padding, newPlayerY + padding, vars)
		|| map_h_wall(newPlayerX + padding, newPlayerY + padding, vars)
	);
}

void	update_player_position(t_init *vars, double new_px, double new_py)
{
	vars->player->player_x = new_px;
	vars->player->player_y = new_py;
}

void	refresh_window(t_init *vars)
{
	mlx_destroy_image(vars->mlx, vars->mlx_img);
	vars->mlx_img = mlx_new_image(vars->mlx, \
		vars->window_width, vars->window_height);
	vars->data_img = mlx_get_data_addr(vars->mlx_img, \
		&vars->bits_per_pixel, &vars->size_line, &vars->endian);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}

int	ft_move_player(t_init *vars)
{
	double	new_px;
	double	new_py;

	animation(vars);
	update_player_rotation(vars);
	calc_np_position(vars, &new_px, &new_py);
	if (!is_collision(new_px, new_py, vars))
	{
		update_player_position(vars, new_px, new_py);
		refresh_window(vars);
	}
	cast_rays(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
	render_player_texture(vars);
	render(vars);
	return (0);
}
