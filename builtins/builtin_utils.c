/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:25:50 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:25:50 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ptr_count(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	check_empty(char *line)
{
	while (*line)
	{
		if (*line != 32 && !(*line >= 9 && *line <= 13))
			return (0);
		line++;
	}
	return (1);
}

char	**get_var_adress(const char *name)
{
	char	**ptr;
	int		len;

	len = ft_strlen(name);
	ptr = environ;
	if (!(*ptr))
		return (ptr);
	while (ft_strncmp(*ptr, name, len)
		|| ((*ptr)[len] != '=' && (*ptr)[len] != 0))
	{
		ptr++;
		if (!(*ptr))
			break ;
	}
	return (ptr);
}

int	ft_dist(int (*func)(), t_pipe_list *cmd)
{
	int	in_buff;
	int	out_buff;
	int	ret;

	ret = 0;
	if (cmd->in_fd)
	{
		in_buff = dup(STDIN_FILENO);
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	if (cmd->out_fd)
	{
		out_buff = dup(STDOUT_FILENO);
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	ret = func(cmd->cmd);
	if (cmd->in_fd)
		dup2(in_buff, STDIN_FILENO);
	if (cmd->out_fd)
		dup2(out_buff, STDOUT_FILENO);
	return (ret);
}
