/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:59:42 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/13 12:14:49 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_save(const char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (0);
		else
			i++;
	}
	return (1);
}

static int	cnt_len(const char *c, const char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = (int) ft_strlen(c);
	while (char_to_save(c[i], str) == 0 && c[i])
	{
		cnt--;
		i++;
	}
	if (cnt == 0)
		return (cnt);
	i = (int) ft_strlen(c) - 1;
	while (char_to_save(c[i], str) == 0 && i > 0)
	{
		cnt--;
		i--;
	}
	return (cnt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		z;

	z = 0;
	i = 0;
	if (!s1)
		return (NULL);
	j = (int) ft_strlen(s1) - 1;
	if (!set)
		return (ft_strdup(s1));
	if (cnt_len(s1, set) == 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (cnt_len(s1, set) + 1));
	if (!str)
		return (NULL);
	while (char_to_save(s1[i], set) == 0 && s1[i])
		i++;
	while (char_to_save(s1[j], set) == 0)
		j--;
	while (i <= j && s1[i])
		str[z++] = s1[i++];
	str[z] = 0;
	return (str);
}
