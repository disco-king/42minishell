/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:03:38 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 10:03:38 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mem(t_pipe_list **cmd, char **arr, t_list **tokens)
{
	if (cmd && *cmd)
		*cmd = free_lst(*cmd);
	if (arr)
		free_all(arr);
	if (tokens)
		list_clear(tokens);
}

int	redir_handler(t_pipe_list *cmd, int last_ret)
{
	int	ret;

	ret = ft_infile(cmd, last_ret);
	if (ret)
	{
		if (ret == 1)
			print_error("syntax error", "filename not found", NULL);
	}
	else
	{
		ret = ft_outfile(cmd);
		if (ret == 1)
			print_error("syntax error", "filename not found", NULL);
	}
	return (ret);
}

t_pipe_list	*main_parsing(char *line, t_shell *shell)
{
	t_pipe_list	*cmd;

	if (ft_parser(line, shell))
	{
		free_mem(NULL, shell->awk, &shell->tokens);
		return (NULL);
	}
	cmd = trim_token(shell->awk, *shell, shell->tokens);
	if (!cmd)
		free_mem(NULL, shell->awk, &shell->tokens);
	else if (redir_handler(cmd, shell->last_ret))
		free_mem(&cmd, shell->awk, &shell->tokens);
	return (cmd);
}

void	exec_module(t_pipe_list *cmd, t_shell *shell)
{
	signal(SIGINT, interrupt_cmd);
	if (shell->pipe)
	{
		if (cmd)
			pipeline(cmd, shell);
		shell->pipe = 0;
	}
	else if (builtins(cmd, shell))
		shell->last_ret = exec(cmd->cmd, cmd->in_fd, cmd->out_fd);
	signal(SIGINT, interrupt);
	free_mem(&cmd, shell->awk, &shell->tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_pipe_list	*cmd;
	char		*line;
	char		**buff;

	buff = new_env(&shell);
	environ = buff;
	signals();
	catch_signals();
	shell_init(&shell);
	while (1)
	{
		shell.pipe = 0;
		line = readline("\e[0;32mmy_shell$>\e[0;39m ");
		if (ft_exit(line, shell.env_len))
			continue ;
		add_history(line);
		cmd = main_parsing(line, &shell);
		if (!cmd)
			continue ;
		exec_module(cmd, &shell);
	}
}
