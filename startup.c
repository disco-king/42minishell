/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:30:03 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 12:03:48 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_init(t_shell *shell)
{
	if (!environ)
	{
		print_error("fatal", "environ allocation failed", NULL);
		exit(1);
	}
	get_shlvl(shell);
	shell->last_ret = 0;
	shell->pipe = 0;
	shell->awk = NULL;
	shell->tokens = NULL;
}

void	catch_signals(void)
{
	int		pid;
	char	**cmd;

	if (pid < 0)
		return ;
	cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("stty");
	cmd[1] = ft_strdup("-echoctl");
	cmd[2] = NULL;
	exec(cmd, 0, 0);
	free_all(cmd);
}
