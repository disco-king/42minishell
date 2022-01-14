/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 19:10:13 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 19:10:13 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(int code)
{
	int	ret;

	if WIFSIGNALED(code)
		ret = WTERMSIG(code) + 128;
	else
		ret = WEXITSTATUS(code);
	return (ret);
}
