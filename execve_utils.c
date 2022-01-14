/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:42:21 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 13:17:57 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_exit(int code)
{
	if (code == 1)
		print_error("exec", "file not opened", NULL);
	else if (code == 2)
		print_error("exec", "execution failed", NULL);
	else if (code == 3)
		print_error("exec", "bad executable", NULL);
	else if (code == 4)
		print_error("exec", "incorrect arguments", NULL);
	else if (code == 5)
		print_error("exec", "forking failed", NULL);
	else if (code == 6)
		print_error("exec", "malloc problem", NULL);
	return (code);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*dupl;
	char	*buff;

	i = 0;
	if (!cmd || !path)
		close_exit (6);
	if (access(cmd, X_OK) == 0)
		return (ft_strjoin(NULL, cmd));
	dupl = ft_strjoin("/", cmd);
	while (path[i])
	{
		buff = ft_strjoin(path[i], dupl);
		if (access(buff, X_OK) == 0)
		{
			free(dupl);
			return (buff);
		}
		free(buff);
		i++;
	}
	free(dupl);
	return (NULL);
}

int	get_cmd(char **argv)
{
	char	**path;
	char	*cmd;

	if (*argv == NULL || check_empty(*argv))
		return (2);
	cmd = getenv("PATH");
	if (!cmd)
		return (1);
	path = ft_split(getenv("PATH"), ':');
	if (!check_builtin(argv[0]))
	{
		free_all(path);
		return (0);
	}
	cmd = check_access(argv[0], path);
	free_all(path);
	if (cmd)
	{
		free(argv[0]);
		argv[0] = cmd;
	}
	else
		return (1);
	return (0);
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
}
