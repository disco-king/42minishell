/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:40:28 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 21:49:59 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_out_fd(t_pipe_list *cmd, int i)
{
	if (cmd->out_fd)
		cmd->out_fd = close(cmd->out_fd);
	if (!cmd->cmd[i + 1])
		return (1);
	if (!ft_strncmp(cmd->cmd[i], APPEND, 2) \
	&& ft_strncmp(cmd->cmd[i + 1], STR_OUTFILE, 1))
	{
		cmd->out_fd = open(cmd->cmd[i + 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (ft_strncmp(cmd->cmd[i + 1], STR_OUTFILE, 1))
		cmd->out_fd = open(cmd->cmd[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->out_fd < 0)
		return (redirect_error(cmd->cmd[i + 1]));
	return (0);
}

int	ft_outfile(t_pipe_list *cmd)
{
	char	**tmp;
	int		i;
	int		ret;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
		{
			if (!ft_strncmp(cmd->cmd[i], STR_OUTFILE, 1))
			{
				ret = get_out_fd(cmd, i);
				if (ret)
					return (ret);
				tmp = cut_redirect(cmd->cmd, STR_OUTFILE);
				free_all(cmd->cmd);
				cmd->cmd = tmp;
				i = -1;
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	get_in_fd(t_pipe_list *cmd, int i, int *heredoc, char **del)
{
	char	**tmp;

	if (cmd->in_fd)
		cmd->in_fd = close(cmd->in_fd);
	if (!cmd->cmd[i + 1])
		return (1);
	else if (!ft_strncmp(cmd->cmd[i], HEREDOC, 2) \
	&& ft_strncmp(cmd->cmd[i + 1], STR_INFILE, 1))
	{
		if (cmd->cmd[i + 1])
			*del = ft_strdup(cmd->cmd[i + 1]);
		*heredoc = 1;
	}
	else if (ft_strncmp(cmd->cmd[i + 1], STR_INFILE, 1))
		cmd->in_fd = open(cmd->cmd[i + 1], O_RDONLY);
	if (cmd->in_fd < 0)
		return (redirect_error(cmd->cmd[i + 1]));
	tmp = cut_redirect(cmd->cmd, STR_INFILE);
	free_all(cmd->cmd);
	cmd->cmd = tmp;
	return (0);
}

int	ft_infile(t_pipe_list *cmd, int last_ret)
{
	int		heredoc;
	char	*del;
	int		i;
	int		ret;

	while (cmd)
	{
		i = 0;
		heredoc = 0;
		while (cmd->cmd[i])
		{
			if (!ft_strncmp(cmd->cmd[i], STR_INFILE, 1))
			{
				ret = get_in_fd(cmd, i, &heredoc, &del);
				if (ret)
					return (ret);
				i = -1;
			}
			i++;
		}
		if (heredoc)
			cmd->in_fd = heredoc_handler(cmd->cmd, del, last_ret);
		cmd = cmd->next;
	}
	return (0);
}
