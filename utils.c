/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:04:14 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 17:49:38 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_digits(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == 0)
		return (1);
	return (0);
}

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 4))
		return (0);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (0);
	else if (!ft_strncmp(cmd, "export", 7))
		return (0);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (0);
	else if (!ft_strncmp(cmd, "env", 4))
		return (0);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (0);
	return (1);
}

int	builtins(t_pipe_list *cmd, t_shell *shell)
{
	if (cmd->cmd[0] == NULL)
		return (1);
	if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		shell->last_ret = ft_dist(&ft_pwd, cmd);
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		shell->last_ret = ft_dist(&ft_cd, cmd);
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		shell->last_ret = export_parse(cmd->cmd, shell);
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		shell->last_ret = unset_cycle(cmd->cmd);
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		shell->last_ret = ft_dist(&ft_env, cmd);
	else if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		shell->last_ret = ft_dist(&ft_echo, cmd);
	else
		return (1);
	return (0);
}

int	get_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*num_str;

	shlvl = ft_atoi(getenv("SHLVL"));
	num_str = ft_itoa(shlvl + 1);
	if (shlvl < 1 || !num_str)
		return (1);
	ft_export("SHLVL=", num_str, shell);
	free(num_str);
	return (0);
}

char	**new_env(t_shell	*shell)
{
	char	**buff;
	int		count;

	count = ptr_count(environ);
	buff = (char **)malloc((count + 1) * sizeof(char *));
	if (!buff)
		return (NULL);
	buff[count] = NULL;
	shell->env_len = count + 1;
	count = 0;
	while (environ[count])
	{
		if (!ft_strncmp(environ[count], "LINES=", 6)
			|| !ft_strncmp(environ[count], "COLUMNS=", 8))
			buff[count] = environ[count];
		else
			buff[count] = ft_strdup(environ[count]);
		if (!buff[count])
		{
			free_all(buff);
			return (NULL);
		}
		count++;
	}
	return (buff);
}
