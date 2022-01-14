/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:12:30 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 10:12:37 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char c)
{
	if (c == CHAR_NEWLINE || c == CHAR_SPACE || c == CHAR_TAB || c == CHAR_PIPE \
		|| c == CHAR_INFILE || c == CHAR_OUTFILE)
		return (0);
	return (1);
}

int	ft_dollar(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	quote_error(void)
{
	print_error("parsing", "quote error", NULL);
	return (1);
}

int	is_redirect(char c)
{
	if (c == '<' || c == '>')
	{
		print_error("parsing", "syntax error", NULL);
		return (1);
	}
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 14) || c == 32)
		return (1);
	return (0);
}
