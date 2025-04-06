/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:11:26 by smarsi            #+#    #+#             */
/*   Updated: 2025/01/29 18:19:58 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static	int	count_word(char const *s, char c)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		if (s[i] == c)
		{
			count++;
			flag = 1;
		}
		i++;
	}
	return (count);
}

static	char	*get_word(char *dst, char const *src, char c, int	*index)
{
	int	i;
	int	start;
	int	len;

	i = *index;
	start = i;
	while (src[i])
	{
		if (src[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	len = (i - start) + 1;
	dst = ft_calloc(len, sizeof(char));
	ft_strlcpy(dst, src + start, len);
	*index = i;
	return (dst);
}

static char	**fill_array(char **dst, char const *src, char c, int number_word)
{
	int	i;
	int	index_word;

	index_word = 0;
	i = 0;
	while (i < number_word)
	{
		dst[i] = get_word(dst[i], src, c, &index_word);
		if (!dst[i])
			ft_free(dst);
		i++;
	}
	return (dst);
}

char	**my_split(char const *s, char c)
{
	char	**dst;
	int		count;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	dst = ft_calloc(count + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	dst = fill_array(dst, s, c, count);
	return (dst);
}
