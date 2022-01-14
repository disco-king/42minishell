/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 00:02:01 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 11:34:43 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds_pipeline(t_pipe_list *lst)
{
	while (lst)
	{
		close_fds(lst->in_fd, lst->out_fd);
		lst = lst->next;
	}
}

int	pipeline_error(t_pipe_list *lst, char *try_cmd)
{
	if (!try_cmd)
		return (0);
	if (!ft_strncmp(try_cmd, "(null)", ft_strlen(try_cmd) + 1))
	{
		free(try_cmd);
		print_error("pipeline", "no command found", NULL);
	}
	else
		print_error(try_cmd, "command not found", NULL);
	close_fds_pipeline(lst);
	return (127);
}

void	get_fds(t_pipe_list *cmd, int read_fd, int p_writer)
{
	if (read_fd)
	{
		if (cmd->in_fd)
			close(read_fd);
		else if (cmd->in_fd == 0)
			cmd->in_fd = read_fd;
	}
	if (cmd->out_fd == 0 && p_writer)
		cmd->out_fd = p_writer;
}

void	dup_io(t_pipe_list *cmd)
{
	if (cmd->out_fd)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	if (cmd->in_fd)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
}

int	pipe_ret_error(int code, int in_fd, int out_fd)
{
	if (code == -1)
		perror("msh: pipe");
	if (code == -2)
		perror("msh: fork");
	else
		code = -3;
	return (code);
}
