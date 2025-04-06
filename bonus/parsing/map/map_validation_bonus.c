/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:29:54 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/30 16:18:25 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

void	ft_print(t_data *data, char **test)
{
	int	i;

	i = 0;
	if (!test)
		return ;
	while (test[i])
	{
		i++;
	}
	(void) data;
	(void) test;
}

void	check_empty_line_map(t_data *data)
{
	char	*line;

	int (i), (j), (flag);
	i = 0;
	flag = 0;
	if (!data)
		return ;
	while (data->map_structure_clone[i])
	{
		j = 0;
		line = data->map_structure_clone[i];
		while (line[j] && in_array(line[j], " \t"))
			j++;
		if (line[j] && line[j] == '\n')
		{
			flag = 1;
			i++;
			continue ;
		}
		if (flag && line[j] && in_array(line[j], "0 1NSEWDA\n"))
			print_error(data, "New lines are not allowed between map entries.");
		i++;
	}
}

void	check_map(t_data *data)
{
	char	*line;

	int (i), (j);
	if (!data || !data->map_structure_clone)
		return ;
	i = 0;
	check_empty_line_map(data);
	while (data->map_structure_clone[i])
	{
		j = 0;
		line = data->map_structure_clone[i];
		while (line[j])
		{
			if (!in_array(line[j], "0 1NSEWDA\n"))
				print_error(data, "There is a bad character in the map.");
			j++;
		}
		i++;
	}
}
