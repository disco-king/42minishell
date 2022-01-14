/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:53:45 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 22:53:45 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe_list	*pipe_lstnew(char **content)
{
	t_pipe_list	*new;

	new = (t_pipe_list *)malloc(sizeof(t_pipe_list));
	if (!new)
		return (NULL);
	new->in_fd = 0;
	new->out_fd = 0;
	new->cmd = content;
	new->next = NULL;
	return (new);
}

void	add_pipe_list(t_pipe_list **start, char **str)
{
	t_pipe_list	*ptr;
	t_pipe_list	*new;

	if (!(*start))
	{
		*start = pipe_lstnew(str);
		return ;
	}
	ptr = *start;
	new = pipe_lstnew(str);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_pipe_list	*free_lst(t_pipe_list *list)
{
	t_pipe_list	*buff;

	if (!list)
		return (NULL);
	buff = list->next;
	while (list->next)
	{
		free_all(list->cmd);
		free(list);
		list = buff;
		buff = buff->next;
	}
	free_all(list->cmd);
	free(list);
	return (NULL);
}

char	*get_list(t_pipe_list *cmds)
{
	t_pipe_list	*lst;
	int			ret;

	lst = cmds;
	while (cmds)
	{
		ret = get_cmd(cmds->cmd);
		if (ret == 1)
			return (cmds->cmd[0]);
		else if (ret == 2)
			return (ft_strdup("(null)"));
		cmds = cmds->next;
	}
	return (NULL);
}
