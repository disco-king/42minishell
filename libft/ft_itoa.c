/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:01:02 by tcharmel          #+#    #+#             */
/*   Updated: 2021/05/04 16:25:04 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_zeros(long int k)
{
	int	i;

	i = 0;
	if (k < 0)
	{
		i++;
		k *= -1;
	}
	if (k == 0)
		return (i = 1);
	while (k > 0)
	{
		k /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	j;

	j = n;
	i = ft_zeros(j);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = 0;
	if (j == 0)
		str[0] = '0';
	if (j < 0)
	{
		str[0] = '-';
		j *= -1;
	}
	while (j > 0)
	{
		str[i - 1] = j % 10 + 48;
		j = j / 10;
		i--;
	}
	return (str);
}
