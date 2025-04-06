/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation_helper_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:49 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 16:18:53 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	textures_extension(t_data *data, char *texture)
{
	size_t	len;

	len = ft_strlen(texture) - 4;
	if (ft_strcmp(texture + len, ".xpm") || len == 0)
		print_error(data, "Texture names should have a .xpm extension");
}

long long	my_atoi(t_data *data, char *str)
{
	long long	signe;
	long long	digit;

	digit = 0;
	signe = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		print_error(data, "[+ && -] Not a valid RGB syntax");
	}
	while (ft_isdigit(*str))
	{
		digit = (digit * 10 + *str) - '0';
		str++;
	}
	return (digit * signe);
}

void	validate_texture_path_helper(t_data *data, char *texture, int index)
{
	if (texture && is_withspace(texture[index]))
	{
		while (texture[index] && is_withspace(texture[index]))
			index++;
	}
	else
	{
		ft_putstr_fd("Error\nInvalid '", 2);
		texture[index] = '\0';
		ft_putstr_fd(texture, 2);
		ft_putstr_fd("' texture. Expected: '", 2);
		ft_putstr_fd(texture, 2);
		print_error(data, "\0");
	}
}

void	validate_texture_path(t_data *data)
{
	if (data && data->texture_north)
		validate_texture_path_helper(data, data->texture_north, 2);
	if (data && data->texture_south)
		validate_texture_path_helper(data, data->texture_south, 2);
	if (data && data->texture_west)
		validate_texture_path_helper(data, data->texture_west, 2);
	if (data && data->texture_east)
		validate_texture_path_helper(data, data->texture_east, 2);
}

void	check_identifiers(t_data *data, char *line)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (data->counters[i] == 0)
		{
			if (in_array(line[0], "01NSEWDA\n"))
				print_error(data, "Identifier: \
[Invalid Position | Not Found | Invalid]");
			print_error(data, "There is a bad character in the file.");
		}
		i++;
	}
}
