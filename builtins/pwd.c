/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:13:05 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 12:13:05 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args)
{
	char	*buff;

	(void) args;
	buff = getcwd(NULL, 0);
	if (!buff)
		ft_putendl_fd(getenv("PWD"), 1);
	else
		ft_putendl_fd(buff, 1);
	free(buff);
	return (0);
}
