/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:51:20 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/02 15:17:00 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	*ptr_s;

	i = 0;
	ptr_s = (unsigned char *) s;
	while (ptr_s[i] != '\0')
	{
		if (ptr_s[i] == (unsigned char)c)
			return ((char *)&ptr_s[i]);
		i++;
	}
	if (c == '\0' || c == 1024)
		return ((char *)&ptr_s[i]);
	return (0);
}
