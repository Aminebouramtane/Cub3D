/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_comma.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:30:24 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 10:30:25 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	handle_comma(t_data *data, int *flag, int *count, int *i)
{
	if (*flag != 2)
		print_error(data, "Invalid color: \
(either invalid or missing) [,].");
	else if (*flag == 2)
	{
		*flag = 1;
		(*count)++;
		(*i)++;
	}
}

void	count_comma_number(t_data *data, int comma_count, int digit_count)
{
	if (comma_count != 2)
		print_error(data, "Invalid color:\
 (either invalid or missing) [,].");
	if (digit_count != 3)
		print_error(data, "R,G,B colors must be in range [0,255]:\
 0, 255, 255");
}

void	valid_rgb_range(t_data *data, char *texture, int *index)
{
	int	i;

	i = *index;
	if (my_atoi(data, texture + i) < 0 || \
	my_atoi(data, texture + i) > 255)
		print_error(data, "R,G,B colors must be in range\
 [0,255]: 0, 255, 255");
	if (texture[i] == '+')
		i++;
	*index = i;
}

void	valid_comma(t_data *data, char *texture)
{
	int (i), (flag), (count), (digit_count);
	count = 0;
	i = 0;
	flag = 1;
	digit_count = 0;
	while (texture[i])
	{
		if (texture[i] == ',')
			handle_comma(data, &flag, &count, &i);
		else if (flag == 1 && (texture[i] == '+' || ft_isdigit(texture[i])))
		{
			valid_rgb_range(data, texture, &i);
			while (texture[i] && ft_isdigit(texture[i]))
				i++;
			flag = 2;
			digit_count++;
		}
		else if (texture[i] && ft_isdigit(texture[i]) && flag == 2)
			print_error(data, "R,G,B colors must be in range [0,255]:\
 0, 255, 255");
		while (texture[i] && in_array(texture[i], " \t\n"))
			i++;
	}
	count_comma_number(data, count, digit_count);
}
