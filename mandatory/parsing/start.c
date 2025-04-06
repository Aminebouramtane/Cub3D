/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:40 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 10:30:41 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	valid_map_name(char *name)
{
	size_t	len;

	len = ft_strlen(name) - 4;
	if (ft_strcmp(name + len, ".cub") || len == 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Map name should have a .cub extension", 2);
		exit (1);
	}
}

static void	valid_map_path(char *name)
{
	int	fd;

	fd = open(name, __O_DIRECTORY);
	if (fd != -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("Not a File.\n", 2);
		close (fd);
		exit(1);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd("The provided path is incorrect.\n", 2);
		exit(1);
	}
	close (fd);
}

void	check_empty_map(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (data && data->full_map_data && data->full_map_data[i])
	{
		line = data->full_map_data[i];
		if (!line)
			return ;
		while (*line && (*line <= 32 || *line == '\n'))
			line++;
		if (line && line[0])
			return ;
		i++;
	}
}

void	check_all_identifiers(t_data *data)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (data->counters[i] == 0)
			print_error(data, "Map invalid.");
		i++;
	}
}

void	parsing_part(char *av[], t_data *data)
{
	valid_map_name(av[1]);
	valid_map_path(av[1]);
	parse_map_file(av[1], data);
	get_texture_config(data);
	get_color(data);
	if (!data->map_structure_clone)
		print_error(data, "Empty Map.");
	textures_extension(data, data->texture_north);
	textures_extension(data, data->texture_south);
	textures_extension(data, data->texture_east);
	textures_extension(data, data->texture_west);
	check_all_identifiers(data);
	parsing_map(data);
}
