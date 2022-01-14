/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:36:01 by tcharmel          #+#    #+#             */
/*   Updated: 2021/05/06 18:19:05 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*s1;
	unsigned char	a;

	a = c;
	s1 = s;
	while (*s)
		s++;
	if (!a)
		return ((char *)s);
	while (s >= s1)
	{
		if (*s == a)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
