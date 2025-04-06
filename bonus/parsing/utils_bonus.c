/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:57 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 18:20:09 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	print_error(t_data *data, char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	if (data->full_map_data)
		ft_free(data->full_map_data);
	if (data->map_structure)
		ft_free(data->map_structure);
	if (data->map_structure_clone)
		ft_free(data->map_structure_clone);
	exit (1);
}

int	in_array(char to_search, char *search_in)
{
	int	i;

	i = 0;
	while (search_in && search_in[i])
	{
		if (search_in[i] == to_search)
			return (1);
		i++;
	}
	return (0);
}

void	print_repeated(t_data *data, int i)
{
	if (i == 0)
		print_error(data, "[NO] Texture repeated.");
	if (i == 1)
		print_error(data, "[SO] Texture repeated.");
	if (i == 2)
		print_error(data, "[WE] Texture repeated.");
	if (i == 3)
		print_error(data, "[EA] Texture repeated.");
	if (i == 4)
		print_error(data, "[F] Texture repeated.");
	if (i == 5)
		print_error(data, "[C] Texture repeated.");
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	skip_space(char **line)
{
	while (line && *line && **line && **line == 32)
		(*line)++;
}
