/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:04:02 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/02 15:05:51 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*pointer;

	i = 0;
	pointer = malloc(count * size);
	if (!pointer)
		return (0);
	while (i < (count * size))
	{
		pointer[i] = 0;
		i++;
	}
	return (pointer);
}
