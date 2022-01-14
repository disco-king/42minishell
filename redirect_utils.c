/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:44:37 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 21:44:43 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_error(char *filename)
{
	ft_putstr_fd(NAME, 2);
	ft_putstr_fd(": ", 2);
	perror(filename);
	return (2);
}

static int	get_cut_length(char **cmd, char *redir)
{
	int	cut;
	int	i;
	int	j;

	i = 0;
	j = 0;
	cut = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], redir, 1) && !cut)
		{
			cut = 1;
			if (!ft_strncmp(cmd[i + 1], redir, 1))
				i++;
			i += 2;
			continue ;
		}
		i++;
		j++;
	}
	return (j);
}

char	**cut_redirect(char **cmd, char *redir)
{
	char	**str;
	int		cut;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cut = 0;
	str = (char **)malloc(sizeof(char *) * (get_cut_length(cmd, redir) + 1));
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], redir, 1) && !cut)
		{
			cut = 1;
			if (!ft_strncmp(cmd[i + 1], redir, 1))
				i++;
			i += 2;
			continue ;
		}
		str[j] = ft_strdup(cmd[i]);
		j++;
		i++;
	}
	str[j] = NULL;
	return (str);
}
