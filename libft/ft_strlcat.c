/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:46:04 by tcharmel          #+#    #+#             */
/*   Updated: 2021/04/26 23:29:37 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(src);
	k = ft_strlen(dst);
	if (k >= size)
		return (size + i);
	if (i + k < size)
		ft_memcpy(dst + k, src, i + 1);
	else
	{
		size = size - k;
		ft_memcpy(dst + k, src, size - 1);
		dst[k + size - 1] = '\0';
	}
	return (k + i);
}
