/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:58:41 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/13 12:14:17 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*str;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	str = (char *)malloc(len);
	if (str == 0)
		return (NULL);
	return ((char *)ft_memcpy(str, s1, len));
}
