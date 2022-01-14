/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:42:51 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 22:40:41 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	if (s1[0] == 0)
		return (1);
	while (s1[i])
	{
		if (s2[i] == 0)
			return (1);
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*parse_heredoc_add(char *line, int j, int last_ret)
{
	t_tmp	data;
	char	*str;

	data.i = 0;
	data.tmp = 0;
	data.last_ret = last_ret;
	str = malloc(j + 2);
	while (line[data.tmp])
	{
		if (line[data.tmp] == '$')
		{
			add_env(line, str, &data);
			continue ;
		}
		str[data.i] = line[data.tmp];
		data.tmp++;
		data.i++;
	}
	str[data.i] = '\n';
	str[data.i + 1] = 0;
	return (str);
}

static char	*parse_heredoc(char *line, int last_ret)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$' && ft_dollar(line[i + 1]))
		{
			env_cnt_mem(line, &i, &j, last_ret);
			continue ;
		}
		i++;
		j++;
	}
	return (parse_heredoc_add(line, j, last_ret));
}

static int	heredoc_input(char *text)
{
	int	pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("msh: pipe");
		return (0);
	}
	ft_putstr_fd(text, pfd[1]);
	close(pfd[1]);
	free(text);
	return (pfd[0]);
}

int	heredoc_handler(char **cmd, char *del, int last_ret)
{
	char	*line;
	char	*buf;
	char	*tmp;

	buf = NULL;
	tmp = NULL;
	line = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (!is_delimiter(line, del))
			break ;
		tmp = parse_heredoc(line, last_ret);
		free(line);
		line = ft_strjoin(buf, tmp);
		free(buf);
		buf = line;
		free(tmp);
	}
	free(line);
	free(del);
	return (heredoc_input(buf));
}
