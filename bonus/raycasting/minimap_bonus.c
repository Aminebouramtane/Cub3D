/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:50:04 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 11:17:07 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_rectangle(t_init *vars, t_rect *rect)
{
	int	i;
	int	j;
	int	offset;

	if (rect->x < 0 || rect->y < 0 || rect->x >= MINIMAP_WIDTH
		|| rect->y >= MINIMAP_HEIGHT)
		return ;
	i = rect->y;
	while (i < rect->y + rect->height && i < MINIMAP_HEIGHT)
	{
		j = rect->x;
		while (j < rect->x + rect->width && j < MINIMAP_WIDTH)
		{
			offset = (i * vars->size_line) + (j * (vars->bits_per_pixel / 8));
			*(unsigned int *)(vars->data_img + offset) = rect->color;
			j++;
		}
		i++;
	}
}

void	render_player(t_init *vars, int flag)
{
	t_rect	player_rect;

	if (flag == 0)
	{
		player_rect.width = vars->player->width;
		player_rect.height = vars->player->height;
		player_rect.x = (MINIMAP_WIDTH / 2) - (player_rect.width / 2);
		player_rect.y = (MINIMAP_HEIGHT / 2) - (player_rect.height / 2);
		player_rect.color = 0xFF0000;
		draw_rectangle(vars, &player_rect);
	}
}

void	render_tile(t_init *vars, t_rect *tile_rect, int i, int j)
{
	int	x;
	int	y;

	x = j * vars->tile_size / 3;
	y = i * vars->tile_size / 3;
	tile_rect->x = x - vars->player->player_x / 3 + (MINIMAP_WIDTH / 2);
	tile_rect->y = y - vars->player->player_y / 3 + (MINIMAP_HEIGHT / 2);
	if (tile_rect->x + vars->tile_size / 3 >= 0
		&& tile_rect->x < MINIMAP_WIDTH
		&& tile_rect->y + vars->tile_size / 3 >= 0
		&& tile_rect->y < MINIMAP_HEIGHT
		&& i >= 0 && i < vars->map_rows_num
		&& j >= 0 && j < (int)ft_strlen(vars->map[i]))
	{
		tile_rect->width = vars->tile_size / 3;
		tile_rect->height = vars->tile_size / 3;
		minimap_color(tile_rect, vars->map[i][j]);
		draw_rectangle(vars, tile_rect);
	}
}

void	render_map(t_init *vars)
{
	int		i;
	int		j;
	t_rect	tile_rect;

	i = 0;
	while (i < vars->map_rows_num)
	{
		j = 0;
		while (j < (int)ft_strlen(vars->map[i]))
		{
			render_tile(vars, &tile_rect, i, j);
			j++;
		}
		i++;
	}
}

void	render(t_init *vars)
{
	render_map(vars);
	render_player(vars, 0);
}
