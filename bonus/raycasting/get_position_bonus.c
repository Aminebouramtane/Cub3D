/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:44:11 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 18:20:32 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	get_position_x(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'N' || map[y][x] == 'W')
				return (x);
			x++;
		}
		y++;
	}
	printf("Error: Player not found on map (x).\n");
	return (-1);
}

int	get_position_y(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'N' || map[y][x] == 'W')
				return (y);
			x++;
		}
		y++;
	}
	printf("Error: Player not found on map (y).\n");
	return (-1);
}

size_t	ft_height(t_data *data)
{
	size_t	l;

	l = 0;
	while (data->map_structure[l])
		l++;
	return (l);
}

size_t	ft_max_width(t_data *data)
{
	size_t	i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	while (i < ft_height(data))
	{
		len = ft_strlen(data->map_structure[i]);
		if (max < len)
			max = len;
		i++;
	}
	return (max);
}
