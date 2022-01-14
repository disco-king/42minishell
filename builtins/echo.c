/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:29:30 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:29:30 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args)
{
	char	newline;

	newline = '\n';
	if (!args[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[1] && !ft_strncmp(args[1], "-n", 3))
	{
		args++;
		newline = 0;
	}
	if (!args[1])
		return (0);
	args++;
	while (*(args + 1))
	{
		printf("%s ", *args);
		args++;
	}
	printf("%s%c", *args, newline);
	return (0);
}
