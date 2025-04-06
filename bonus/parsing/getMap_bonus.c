/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getMap_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:31 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 16:24:47 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	get_ceil_color(t_data *data)
{
	int	i;

	i = 2;
	if (data->texture_color)
	{
		while (data->texture_color && i >= 0)
		{
			ft_memset(((char *)&data->ceiling_color) + \
			i--, (int)ft_atoi(data->texture_color), 1);
			while (*data->texture_color && *data->texture_color != ',')
				data->texture_color++;
			if (*data->texture_color && *data->texture_color == ',')
				data->texture_color++;
		}
	}
}

void	get_color(t_data *data)
{
	int	i;

	i = 2;
	if (data->texture_fcolor)
	{
		while (data->texture_fcolor && i >= 0)
		{
			ft_memset(((char *)&data->floor_color) + \
			i--, (int)ft_atoi(data->texture_fcolor), 1);
			while (*data->texture_fcolor && *data->texture_fcolor != ',')
				data->texture_fcolor++;
			if (*data->texture_fcolor && *data->texture_fcolor == ',')
				data->texture_fcolor++;
		}
	}
	get_ceil_color(data);
}

void	parse_map_file(char *name, t_data *data)
{
	char	*buf;
	char	*map;
	int		fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		print_error(data, "The provided path is incorrect.");
	map = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		map = ft_strjoin(map, buf);
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
	data->full_map_data = my_split(map, '\n');
	if (data && (!data->full_map_data || !data->full_map_data[0]))
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Empty File.\n", 2);
		exit(1);
	}
	free(map);
}

void	get_map(t_data *data, int i)
{
	char	*map;

	if (!data || !data->full_map_data)
		return ;
	map = NULL;
	while (data->full_map_data[i])
	{
		map = ft_strjoin(map, data->full_map_data[i]);
		i++;
	}
	data->map_structure = ft_split(map, '\n');
	data->map_structure_clone = my_split(map, '\n');
	if (!data->map_structure || !data->map_structure_clone)
		print_error(data, "Empty Map.");
	free(map);
}
