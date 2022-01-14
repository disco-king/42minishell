/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:09:37 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 12:12:45 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_all(char **ret)
{
	char	**buff;

	buff = ret;
	while (*ret)
	{
		free(*ret);
		*ret = NULL;
		ret++;
	}
	free(*ret);
	*ret = NULL;
	free(buff);
	buff = NULL;
	return (buff);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	count;
	int	need_l;
	int	len;

	len = ft_strlen(haystack);
	if (*needle == '\0')
		return ((char *)haystack);
	count = 0;
	need_l = ft_strlen(needle);
	while (haystack[count])
	{
		if (haystack[count] == *needle && count + need_l <= len)
			if (ft_strncmp(&(haystack[count]), needle, need_l) == 0)
				return ((char *)&haystack[count]);
		count++;
	}
	return (NULL);
}

void	print_tokens(t_list *lst)
{
	while (lst)
	{
		if (!ft_strncmp(lst->tok, "exit", 4))
			exit (0);
		printf("token: %s\n", lst->tok);
		lst = lst->next;
	}
}

void	print_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("token: %s\n", arg[i]);
		i++;
	}
}

void	print_error(char *cmd, char *error, char *arg)
{
	char	*buff;

	buff = ft_strjoin(arg, error);
	write(2, NAME, ft_strlen(NAME));
	write(2, ": ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, buff, ft_strlen(buff));
	write(2, "\n", 1);
	free(buff);
}
