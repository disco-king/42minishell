/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:32:07 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:32:07 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_exit(char **args, int len)
{
	int	i;

	i = 0;
	if (args)
		free_all(args);
	while (i < len)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

int	get_code_and_exit(char **args, int count)
{
	ft_putstr_fd("exit\n", 1);
	if (count == 1)
		count = 0;
	if (count == 2)
	{
		if (all_digits(args[1]))
			count = ft_atoi(args[1]);
		else
		{
			count = 2;
			print_error("exit", ": numeric argument required", args[1]);
		}
	}
	free_all(args);
	exit(count);
}

static int	line_check(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(line);
		exit(0);
	}
	if (check_empty(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	ft_exit(char *line, int env_len)
{
	char	**args;
	int		count;

	if (line_check(line))
		return (1);
	if (ft_strncmp(line, "exit", 5) && ft_strncmp(line, "exit ", 5))
		return (0);
	args = ft_split(line, ' ');
	count = ptr_count(args);
	free(line);
	if (count > 2)
	{
		print_error("exit", "too many arguments", NULL);
		free_all(args);
		return (1);
	}
	return (get_code_and_exit(args, count));
}
