/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:35:51 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 18:13:39 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_char(t_list *lst)
{
	char	**arg;
	int		j;

	j = 0;
	arg = (char **)malloc(sizeof(char *) * (get_arglen(lst) + 1));
	while (lst)
	{
		arg[j] = lst->tok;
		j++;
		lst = lst->next;
	}
	arg[j] = NULL;
	return (arg);
}

int	get_infile(t_shell *shell, char *line, int *i)
{
	while (is_space(line[*i + 1]))
	{
		*i += 1;
		if (is_redirect(line[*i + 1]))
			return (1);
	}
	if (line[*i + 1] == CHAR_OUTFILE)
	{
		print_error("parsing", "syntax error", NULL);
		return (1);
	}
	if (line[*i + 1] == CHAR_INFILE)
	{
		*i += 1;
		while (is_space(line[*i + 1]))
			*i += 1;
		if (is_redirect(line[*i + 1]))
			return (1);
		add_list(&(shell->tokens), HEREDOC, 1);
		return (0);
	}
	add_list(&(shell->tokens), STR_INFILE, 1);
	return (0);
}

int	get_outfile(t_shell *shell, char *line, int *i)
{
	while (is_space(line[*i + 1]))
	{
		*i += 1;
		if (is_redirect(line[*i + 1]))
			return (1);
	}
	if (line[*i + 1] == CHAR_INFILE)
	{
		print_error("parsing", "syntax error", NULL);
		return (1);
	}
	if (line[*i + 1] == CHAR_OUTFILE)
	{
		*i += 1;
		while (is_space(line[*i + 1]))
			*i += 1;
		if (is_redirect(line[*i + 1]))
			return (1);
		add_list(&(shell->tokens), APPEND, 1);
		return (0);
	}
	add_list(&(shell->tokens), STR_OUTFILE, 1);
	return (0);
}

int	ft_parser(char *line, t_shell *shell)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (!err && line[i])
	{
		if (line[i] == CHAR_PIPE)
		{
			shell->pipe = 1;
			add_list(&(shell->tokens), STR_PIPE, 1);
		}
		else if (line[i] == CHAR_INFILE)
			err = get_infile(shell, line, &i);
		else if (line[i] == CHAR_OUTFILE)
			err = get_outfile(shell, line, &i);
		else if (!err && !is_space(line[i]))
			err = get_word(&i, line, shell);
		i++;
	}
	shell->awk = lst_to_char(shell->tokens);
	free(line);
	return (err);
}
