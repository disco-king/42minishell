/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:35:06 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 18:42:36 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error(char *cmd, int infile, int outfile)
{
	close_fds(infile, outfile);
	if (cmd)
		print_error(cmd, "command not found", NULL);
	else
		print_error("exec", "no command found", NULL);
	return (127);
}

void	exec_dups(int infile, int outfile)
{
	if (infile > 2)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile > 2)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
}

int	exec(char **cmd, int infile, int outfile)
{
	int	id;
	int	ret;

	if (get_cmd(cmd))
		return (exec_error(cmd[0], infile, outfile));
	id = fork();
	if (!id)
	{
		exec_dups(infile, outfile);
		execve(cmd[0], cmd, environ);
		print_error(cmd[0], "is a directory", NULL);
		exit(126);
	}
	else
	{
		close_fds(infile, outfile);
		signal(SIGINT, SIG_IGN);
		waitpid(id, &ret, 0);
	}
	signal(SIGINT, interrupt);
	return (exit_code(ret));
}
