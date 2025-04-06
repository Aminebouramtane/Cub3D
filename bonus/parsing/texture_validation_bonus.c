/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:53 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 16:18:43 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	is_withspace(int c)
{
	if (c && (c == ' ' || c == '\t' || c == '\n'))
	{
		return (1);
	}
	return (0);
}

void	get_texture(t_data *data, char *line, char **texture, int index)
{
	int (i), (j);
	i = 0;
	if (!data || !line)
		return ;
	if (is_withspace(line[i]))
	{
		while (line[i] && is_withspace(line[i]))
			i++;
		if (!line[i] || line[i] == '\n')
			print_error(data, "Error: Invalid texture.");
		j = i;
		while (line[j] && line[j] != '\n')
			j++;
		line[j] = '\0';
		*texture = line + i;
		data->counters[index]++;
		if (data->counters[index] > 1)
			print_repeated(data, index);
	}
	else
		print_error(data, "Error: Invalid texture.");
}

void	is_valid_texture(t_data *data, char *texture, char c)
{
	int (i), (tmp);
	i = 0;
	while (texture[i] && !in_array(texture[i], " \t"))
		i++;
	tmp = i;
	if (texture)
	{
		while (texture[i] && in_array(texture[i], " \t"))
			i++;
		if (texture[i] && texture[i] != '\n')
		{
			if (c == 'N')
				print_error(data, "Invalid Identifiers [NO].");
			else if (c == 'S')
				print_error(data, "Invalid Identifiers [SO].");
			else if (c == 'W')
				print_error(data, "Invalid Identifiers [WE].");
			else if (c == 'E')
				print_error(data, "Invalid Identifiers [EA].");
		}
		texture[tmp] = '\0';
	}
}

void	check_identifiers_get_map(t_data *data, char *line, int index)
{
	check_identifiers(data, line);
	if (!in_array(line[0], "01NSEWA\n"))
		print_error(data, "There is a bad character in the file.");
	is_valid_texture(data, data->texture_north, 'N');
	is_valid_texture(data, data->texture_south, 'S');
	is_valid_texture(data, data->texture_west, 'W');
	is_valid_texture(data, data->texture_east, 'E');
	is_valid_color(data, data->texture_color, 'C');
	is_valid_color(data, data->texture_fcolor, 'F');
	get_map(data, index);
	check_map(data);
}

void	get_texture_config(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	while (data->full_map_data && data->full_map_data[i])
	{
		line = data->full_map_data[i];
		while (*line && is_withspace(*line))
			line++;
		if (!ft_strncmp(line, "NO", 2))
			get_texture(data, line + 2, &data->texture_north, 0);
		else if (!ft_strncmp(line, "SO", 2))
			get_texture(data, line + 2, &data->texture_south, 1);
		else if (!ft_strncmp(line, "WE", 2))
			get_texture(data, line + 2, &data->texture_west, 2);
		else if (!ft_strncmp(line, "EA", 2))
			get_texture(data, line + 2, &data->texture_east, 3);
		else if (!ft_strncmp(line, "F", 1))
			get_texture(data, line + 1, &data->texture_fcolor, 4);
		else if (!ft_strncmp(line, "C", 1))
			get_texture(data, line + 1, &data->texture_color, 5);
		else if (line && *line)
			return (check_identifiers_get_map(data, line, i));
		i++;
	}
}
