/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:15:29 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 12:15:29 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(const char *name)
{
	char	**ptr;
	int		len;

	len = ft_strlen(name);
	ptr = get_var_adress(name);
	if (!(*ptr))
		return (1);
	free(*ptr);
	while (*ptr)
	{
		ptr[0] = ptr[1];
		ptr++;
	}
	return (0);
}

int	unset_cycle(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		ft_unset(arr[i]);
		i++;
	}
	return (0);
}
