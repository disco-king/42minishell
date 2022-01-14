/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:35:25 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/12 14:35:25 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	rewrite(const char *name, const char *value)
{
	char	**ptr;
	int		len;

	if (!getenv(name))
		return (1);
	ptr = get_var_adress(name);
	len = 0;
	while ((*ptr)[len] != '=')
		len++;
	ft_strlcpy((*ptr) + len + 1, value, ft_strlen(value) + 1);
	return (0);
}

static char	*add_var(const char *name, const char *value)
{
	char	*buff;
	char	*variable;

	if (!value)
		return (ft_strdup(name));
	if (!ft_strlen(value))
		return (ft_strjoin(name, "="));
	buff = ft_strjoin(name, "=");
	if (!buff)
		return (NULL);
	variable = ft_strjoin(buff, value);
	free(buff);
	return (variable);
}

static int	copy_env(const char *name, const char *value, t_shell *shell)
{
	char	**buff;
	int		ptr_num;
	int		i;

	i = 0;
	ft_unset(name);
	ptr_num = ptr_count(environ);
	if (ptr_num + 1 >= shell->env_len)
	{
		buff = (char **)malloc(sizeof(char *) * (ptr_num + 2));
		if (!buff)
			return (-1);
		buff[ptr_num + 1] = 0;
		while (i < ptr_num)
		{
			buff[i] = environ[i];
			i++;
		}
		free(environ);
		shell->env_len = ptr_num + 2;
		environ = buff;
	}
	environ[ptr_num] = add_var(name, value);
	return (i);
}

int	ft_export(const char *name, const char *value, t_shell *shell)
{
	char	*str;
	int		val_len;

	if (!name)
		return (1);
	str = ft_substr((char *)name, '=');
	val_len = ft_strlen(value);
	if (ft_strlen(str) == ft_strlen(name))
	{
		if (getenv(str))
		{
			free(str);
			return (0);
		}
		copy_env(str, NULL, shell);
	}
	else if (getenv(str) != NULL && ft_strlen(getenv(str)) >= val_len)
		rewrite(str, value);
	else
		copy_env(str, value, shell);
	free(str);
	return (0);
}
