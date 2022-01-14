/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:57:17 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 22:57:17 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_to_next(t_pipe_list *cmd, int read_fd)
{
	int	pfd[2];
	int	pid;

	if (pipe(pfd) == -1)
		return (pipe_ret_error(-1, cmd->in_fd, cmd->out_fd));
	get_fds(cmd, read_fd, pfd[1]);
	pid = fork();
	if (pid < 0)
		return (pipe_ret_error(-2, cmd->in_fd, cmd->out_fd));
	if (pid)
	{
		close_fds(cmd->in_fd, cmd->out_fd);
		close(pfd[1]);
	}
	else
	{
		dup_io(cmd);
		close_fds(pfd[0], pfd[1]);
		execve(cmd->cmd[0], cmd->cmd, NULL);
		exit(2);
	}
	return (pfd[0]);
}

int	final_exec(t_pipe_list *cmd, int read_fd)
{
	int	pid;
	int	ret;

	get_fds(cmd, read_fd, 0);
	pid = fork();
	if (pid < 0)
		return (pipe_ret_error(-2, cmd->in_fd, cmd->out_fd));
	if (pid)
	{
		close_fds(cmd->in_fd, cmd->out_fd);
		waitpid(pid, &ret, 0);
	}
	else
	{
		dup_io(cmd);
		execve(cmd->cmd[0], cmd->cmd, NULL);
		exit(2);
	}
	return (ret);
}

static int	builtin_pipe(t_pipe_list *cmd, int *read_fd, t_shell *shell)
{
	int	pfd[2];

	if (check_builtin(cmd->cmd[0]))
		return (1);
	if (pipe(pfd) == -1)
	{
		perror("msh: pipe");
		return (-1);
	}
	if (!ft_strncmp(cmd->cmd[0], "exit", 5))
	{
		close(pfd[1]);
		*read_fd = pfd[0];
		return (0);
	}
	get_fds(cmd, *read_fd, pfd[1]);
	builtins(cmd, shell);
	*read_fd = pfd[0];
	return (0);
}

int	pipeline(t_pipe_list *lst, t_shell *shell)
{
	int			buff_fd;
	t_pipe_list	*buff;
	char		*try_cmd;

	buff_fd = 0;
	try_cmd = get_list(lst);
	if (try_cmd)
		return (pipeline_error(lst, try_cmd));
	buff = lst;
	while (lst->next && buff_fd >= 0)
	{
		if (builtin_pipe(lst, &buff_fd, shell))
			buff_fd = pipe_to_next(lst, buff_fd);
		lst = lst->next;
	}
	if (buff_fd < 0)
		return (1);
	if (builtin_pipe(lst, &buff_fd, shell))
		shell->last_ret = exit_code(final_exec(lst, buff_fd));
	else
		close(buff_fd);
	return (0);
}
