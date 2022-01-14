/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:24:52 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:24:52 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_vars(t_shell *shell)
{
	char	*str_buff;
	char	**ptr;

	ptr = get_var_adress("OLDPWD");
	free(*ptr);
	*ptr = ft_strjoin("OLDPWD=", getenv("PWD"));
	str_buff = getcwd(NULL, 0);
	ptr = get_var_adress("PWD");
	free(*ptr);
	*ptr = ft_strjoin("PWD=", str_buff);
	free(str_buff);
}

int	ft_cd(char **path, t_shell *shell)
{
	int	res;

	if (!path[1])
		res = chdir(getenv("HOME"));
	else if (!ft_strncmp(path[1], "-", 2))
	{
		if (!getenv("OLDPWD"))
		{
			print_error("cd", "OLDPWD not set", NULL);
			return (1);
		}
		ft_putendl_fd(getenv("OLDPWD"), 1);
		res = chdir(getenv("OLDPWD"));
	}
	else
		res = chdir(path[1]);
	if (res)
		perror("cd");
	else
		handle_vars(shell);
	return (res);
}
