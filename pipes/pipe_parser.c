/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharmel <tcharmel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:06:51 by tcharmel          #+#    #+#             */
/*   Updated: 2022/01/12 21:06:51 by tcharmel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_pipe_cmd(char **str, int i, int j)
{
	char	**buff;
	int		x;
	int		y;

	x = 0;
	y = i - j;
	buff = (char **)malloc(sizeof(char *) * (j + 1));
	while (x < j)
	{
		buff[x] = ft_strdup(str[y]);
		y++;
		x++;
	}
	buff[x] = NULL;
	return (buff);
}

int	pipe_error(char **str, int *i, int *j, t_pipe_list **lst)
{
	if (!str[*i + 1] || ft_strrchr(str[*i + 1], CHAR_PIPE))
	{
		print_error("parsing", "too many pipes", NULL);
		return (1);
	}
	add_pipe_list(lst, get_pipe_cmd(str, *i, *j));
	*j = 0;
	*i += 1;
	return (0);
}

t_pipe_list	*trim_token(char **str, t_shell shell, t_list *tok)
{
	t_pipe_list		*lst;
	int				i;
	int				j;

	i = 0;
	j = 0;
	lst = NULL;
	while (str[i] && tok)
	{
		if (ft_strrchr(str[i], CHAR_PIPE) && tok->type == IS_TOKEN)
		{
			if (pipe_error(str, &i, &j, &lst))
				return (free_lst(lst));
			shell.pipe = 1;
			tok = tok->next;
			continue ;
		}
		i++;
		j++;
		tok = tok->next;
	}
	add_pipe_list(&lst, get_pipe_cmd(str, i, j));
	return (lst);
}

void	print_ptoken(t_pipe_list *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		ft_putstr_fd("pipe commands: ", 2);
		while (lst->cmd[i])
		{
			ft_putstr_fd(lst->cmd[i], 2);
			write(2, " ", 1);
			i++;
		}
		ft_putstr_fd("in_fd=<", 2);
		ft_putnbr_fd(lst->in_fd, 2);
		ft_putstr_fd("> out_fd=<", 2);
		ft_putnbr_fd(lst->out_fd, 2);
		ft_putstr_fd(">\n", 2);
		lst = lst->next;
	}
}
