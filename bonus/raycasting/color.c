/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:30:52 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/31 20:40:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	minimap_color(t_rect *tile_rect, char c)
{
	if (c == '1')
		tile_rect->color = 0xFFFFFF;
	else if (c == 'D')
		tile_rect->color = 0xFF0000;
	else if (c == 'd')
		tile_rect->color = 0x00FF00;
	else if (c == 'A')
		tile_rect->color = 0xFFFF00;
	else
		tile_rect->color = 0x000000;
}

unsigned int	my_get_color(t_init *vars, int x, int y, int index)
{
	int				offset;
	unsigned int	color;
	int				anim_index;

	anim_index = vars->animation->index;
	if (index == 5)
	{
		if (x < 0 || x > vars->animation->width[anim_index]
			|| y < 0 || y > vars->animation->height[anim_index])
			return (0);
		offset = (y * vars->animation->line_size[anim_index])
			+ (x * (vars->animation->bpp[anim_index] / 8));
		color = *(unsigned int *)(vars->animation->data[anim_index] + offset);
	}
	else
	{
		if (x < 0 || x > vars->texture_width[index]
			|| y < 0 || y > vars->texture_height[index])
			return (0);
		offset = (y * vars->texture_line_size[index])
			+ (x * (vars->texture_bpp[index] / 8));
		color = *(unsigned int *)(vars->texture_data[index] + offset);
	}
	return (color);
}
