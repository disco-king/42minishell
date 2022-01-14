/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:11:45 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 19:11:54 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_list(char *str, int type)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (type)
		new->tok = ft_strdup(str);
	else
		new->tok = str;
	new->next = NULL;
	new->prev = NULL;
	new->type = type;
	return (new);
}

void	add_list(t_list **start, char *str, int flag)
{
	t_list	*ptr;
	t_list	*new;

	if (!(*start))
	{
		*start = init_list(str, flag);
		return ;
	}
	ptr = *start;
	new = init_list(str, flag);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}

void	list_clear(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
		tmp = NULL;
	}
}

int	get_arglen(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
