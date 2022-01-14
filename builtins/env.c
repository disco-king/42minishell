/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:30:51 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:30:51 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args)
{
	char	**ptr;
	char	*str;

	if (args[1])
	{
		print_error("env", "too many arguments", NULL);
		return (1);
	}
	ptr = environ;
	while (*ptr)
	{
		str = (char *)get_equals(*ptr);
		if (str[-1] == '=')
		{
			if (*str == 0)
				printf("%s\"\"\n", *ptr);
			else
				printf("%s\n", *ptr);
		}
		ptr++;
	}
	return (0);
}
