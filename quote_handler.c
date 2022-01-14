/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:10:04 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 19:10:05 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	doubleq_handler(char *line, int *tmp, int *j, int last_ret)
{
	*tmp += 1;
	while (line[*tmp] != '\"' && line[*tmp])
	{
		if (line[*tmp] == '$' && ft_dollar(line[*tmp + 1]))
		{
			env_cnt_mem(line, tmp, j, last_ret);
			continue ;
		}
		if (line[*tmp] == CHAR_SLASH)
		{
			*tmp += 1;
			if (line[*tmp] != '\"' && line[*tmp] != '$' && line[*tmp] != '\\')
				*j += 1;
		}
		*tmp += 1;
		*j += 1;
	}
	if (!line[*tmp])
		return (1);
	return (0);
}

int	quote_handler(char *line, int *tmp, int *j)
{
	while (line[++*tmp])
	{
		if (line[*tmp] == '\'')
			break ;
		*j += 1;
	}
	if (!line[*tmp])
		return (1);
	return (0);
}

void	quote_handler_add(char *line, char *str, int *tmp, int *i)
{
	*tmp += 1;
	while (line[*tmp] != '\'')
	{
		str[*i] = line[*tmp];
		*tmp += 1;
		*i += 1;
	}
	*tmp += 1;
}

void	doubleq_handler_add(char *line, char *str, t_tmp *data)
{
	data->tmp += 1;
	while (line[data->tmp] != '\"')
	{
		if (line[data->tmp] == '$' && ft_dollar(line[data->tmp + 1]))
		{
			add_env(line, str, data);
			continue ;
		}
		if (line[data->tmp] == CHAR_SLASH)
		{
			data->tmp += 1;
			if (line[data->tmp] != '\"' && line[data->tmp] != '$'\
			&& line[data->tmp] != '\\')
			{
				str[data->i] = line[data->tmp - 1];
				data->i += 1;
			}
		}
		str[data->i] = line[data->tmp];
		data->tmp += 1;
		data->i += 1;
	}
	data->tmp += 1;
}
