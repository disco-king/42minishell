/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:35:25 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 11:14:43 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exp_add_quotes(char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i] != '=' && str[i])
		write(1, &(str[i++]), 1);
	if (!str[i])
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, &(str[i]), 1);
	i++;
	write(1, "\"", 1);
	while (str[i])
		write(1, &(str[i++]), 1);
	ft_putstr_fd("\"\n", 1);
}

static void	exp_print(void)
{
	int		i;
	char	*str;

	i = 0;
	while (environ[i])
	{
		str = (char *)get_equals(environ[i]);
		if (str[-1] == '=' && *str == 0)
			printf("declare -x %s\"\"\n", environ[i]);
		else
			exp_add_quotes(environ[i]);
		i++;
	}
}

static int	check_name(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] == '_')
		i++;
	while (str[i] != 0 && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

const char	*get_equals(const char *str)
{
	while (*str)
	{
		if (*str == '=')
		{
			str++;
			break ;
		}
		str++;
	}
	return (str);
}

int	export_parse(char **args, t_shell *shell)
{
	char	*buff;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!args[1])
		exp_print();
	while (args[i])
	{
		if (check_name(args[i]))
		{
			print_error("export", ": not a valid identifier", args[i]);
			ret = 1;
		}
		else
			ft_export(args[i], get_equals(args[i]), shell);
		i++;
	}
	return (ret);
}
