/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:27 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 10:30:28 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	is_valid_color(t_data *data, char *texture, char c)
{
	only_valid_characters(data, texture, c);
	valid_comma(data, texture);
}

void	only_valid_characters(t_data *data, char *texture, char c)
{
	int (i);
	i = 0;
	while (texture[i])
	{
		if (!in_array(texture[i], "0123456789, \t\n"))
		{
			if (texture[i] == '+' && texture[i + 1]
				&& ft_isdigit(texture[i + 1]))
			{
				i++;
				continue ;
			}
			else if (texture[i] == '-' && texture[i + 1]
				&& ft_isdigit(texture[i + 1]))
				print_error(data, "R,G,B colors must be in range\
 [0,255]: 0, 255, 255");
			else if (c == 'F')
				print_error(data, "[F]: Invalid Identifiers.");
			else if (c == 'C')
				print_error(data, "[C]: Invalid Identifiers.");
		}
		i++;
	}
}
