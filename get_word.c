/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:19:46 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/13 18:09:57 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	slash_handler(char *line, int *tmp)
{
	*tmp += 1;
	if (!line[*tmp])
		return (1);
	return (0);
}

void	handle_quotes(char *line, char *str, t_tmp *data)
{
	if (line[data->tmp] == '\'')
		quote_handler_add(line, str, &(data->tmp), &(data->i));
	else if (line[data->tmp] == '\"')
		doubleq_handler_add(line, str, data);
	else if (line[data->tmp] == '$' && ft_dollar(line[data->tmp + 1]))
		add_env(line, str, data);
}

char	*get_word_add(char *line, int j, int tmp, int last_ret)
{
	char	*buff;
	t_tmp	data;
	char	*str;

	str = (char *)malloc(sizeof(char) * (j + 1));
	data.tmp = tmp;
	data.i = 0;
	data.last_ret = last_ret;
	while (line[data.tmp] && is_token(line[data.tmp]))
	{
		if (line[data.tmp] == '\\')
			data.tmp++;
		else if (line[data.tmp] == '\'' || line[data.tmp] == '\"' || \
		(line[data.tmp] == '$' && ft_dollar(line[data.tmp + 1])))
		{
			handle_quotes(line, str, &data);
			continue ;
		}
		str[data.i] = line[data.tmp];
		data.tmp++;
		data.i++;
	}
	str[data.i] = 0;
	return (str);
}

int	check_if_quote(char *line, int *tmp, int *j, int last_ret)
{
	if (line[*tmp] == '\\')
		return (slash_handler(line, tmp));
	else if (line[*tmp] == '\'')
		return (quote_handler(line, tmp, j));
	else if (line[*tmp] == '\"')
		return (doubleq_handler(line, tmp, j, last_ret));
	return (0);
}

int	get_word(int *i, char *line, t_shell *shell)
{
	char	*str;
	int		j;
	int		tmp;
	int		err;

	j = 0;
	err = 0;
	tmp = *i;
	while (line[tmp] && is_token(line[tmp]))
	{
		err = check_if_quote(line, &tmp, &j, shell->last_ret);
		if (err)
			return (quote_error());
		if (line[tmp] == '$' && ft_dollar(line[tmp + 1]))
		{
			env_cnt_mem(line, &tmp, &j, shell->last_ret);
			continue ;
		}
		tmp++;
		j++;
	}
	str = get_word_add(line, j, *i, shell->last_ret);
	add_list(&shell->tokens, str, 0);
	*i = tmp - 1;
	return (0);
}
