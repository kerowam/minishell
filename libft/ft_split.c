/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:49:35 by nmontiel          #+#    #+#             */
/*   Updated: 2023/10/30 11:23:57 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	splits(char const *s, char c)
{
	int	i;
	int	split;

	i = 0;
	split = 0;
	while (*s)
	{
		if (*s != c && i == 0)
		{
			i = 1;
			split++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (split);
}

char	*split_word(const char *s, int st, int fn)
{
	char	*str;
	int		i;

	str = (char *)malloc(fn - st + 1);
	if (!str)
		return (0);
	i = 0;
	while (st < fn)
	{
		str[i] = s[st];
		i++;
		st++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str_split;
	size_t	i;
	size_t	o;
	int		pos;

	str_split = malloc((splits(s, c) + 1) * sizeof(char *));
	if (!s || !str_split)
		return (0);
	i = 0;
	o = 0;
	pos = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && pos < 0)
			pos = i;
		else if ((s[i] == c || i == ft_strlen(s)) && pos >= 0)
		{
			str_split[o] = split_word(s, pos, i);
			o++;
			pos = -1;
		}
		i++;
	}
	str_split[o] = 0;
	return (str_split);
}
