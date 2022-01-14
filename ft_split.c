/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:53:06 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 11:53:08 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(char **str)
{
	char	*ptr;
	char	quote;

	ptr = *str;
	quote = *ptr;
	ptr++;
	while (*ptr)
	{
		if (*ptr == quote)
			break ;
		ptr++;
	}
	if (!(*ptr))
		ptr--;
	*str = ptr;
}

static int	word_count(char *str, char sep)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*str)
	{
		if (*str != sep && flag == 0)
		{
			if (*str == 34 || *str == 39)
				skip_quotes(&str);
			count++;
			flag++;
		}
		if (*str == sep)
			flag = 0;
		str++;
	}
	return (count);
}

static char	*get_next_sep(char *str, char sep)
{
	if (*str == 34 || *str == 39)
	{
		skip_quotes(&str);
		str++;
	}
	else
		while (*str != sep && *str)
			str++;
	return (str);
}

static void	check_malloc(char ***ret, int count)
{
	if (count == 0)
		close_exit(4);
	*ret = (char **)malloc((count + 1) * sizeof(char *));
	if (!*ret)
		close_exit(6);
}

char	**ft_split(char *str, char c)
{
	int		count;
	char	**ret;
	char	*buff;
	int		i;

	count = word_count(str, c);
	check_malloc(&ret, count);
	ret[count] = NULL;
	i = count;
	count = 0;
	while (count < i)
	{
		while (*str == c)
			str++;
		buff = ft_substr(str, c);
		if (!buff)
			return (free_all(ret));
		ret[count] = buff;
		str = get_next_sep(str, c);
		count++;
	}
	return (ret);
}
