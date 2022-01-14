/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:37:12 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/13 18:03:52 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *line, char *str, t_tmp *data)
{
	char	*env;
	int		q;
	int		j;

	j = 0;
	q = 0;
	env = env_cnt(line, &data->tmp, data->last_ret);
	if (!env)
		return ;
	while (env[j])
	{
		str[data->i] = env[j];
		data->i += 1;
		j++;
	}
	free(env);
}

char	*env_cnt_add(char *line, int m, int x)
{
	char	*str;
	char	*env;
	int		i;

	i = 0;
	str = malloc(m + 1);
	while (ft_dollar(line[x]))
	{
		str[i] = line[x];
		i++;
		x++;
	}
	str[i] = 0;
	i = 0;
	env = ft_strdup(getenv(str));
	free(str);
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	return (env);
}

char	*env_cnt(char *line, int *tmp, int last_ret)
{
	char	*env;
	int		x;
	int		i;

	i = 0;
	*tmp += 1;
	x = *tmp;
	if (line[*tmp] == '?')
	{
		*tmp += 1;
		env = ft_itoa(last_ret);
		return (env);
	}
	if (!ft_isdigit(line[*tmp]))
		while (ft_dollar(line[*tmp]) && ++*tmp)
			i++;
	else
	{
		*tmp += 1;
		i++;
	}
	env = env_cnt_add(line, i, x);
	return (env);
}

void	env_cnt_mem_add(char *line, int m, int x, int *j)
{
	char	*str;
	char	*env;
	int		i;

	i = 0;
	str = malloc(m + 1);
	while (ft_dollar(line[x]))
	{
		str[i] = line[x];
		i++;
		x++;
	}
	str[i] = 0;
	i = 0;
	env = ft_strdup(getenv(str));
	free(str);
	if (!env)
		return ;
	while (env[i] && ++*j)
		i++;
	free(env);
}

void	env_cnt_mem(char *line, int *tmp, int *j, int last_ret)
{
	char	*env;
	int		x;
	int		i;

	i = 0;
	*tmp += 1;
	x = *tmp;
	if (line[*tmp] == '?')
	{
		*tmp += 1;
		env = ft_itoa(last_ret);
		*j += ft_strlen(env);
		free(env);
		return ;
	}
	if (!ft_isdigit(line[*tmp]))
		while (ft_dollar(line[*tmp]) && ++*tmp)
			i++;
	else
	{
		*tmp += 1;
		i++;
	}
	env_cnt_mem_add(line, i, x, j);
}
