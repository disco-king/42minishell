/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmalphit <fmalphit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:53:37 by fmalphit          #+#    #+#             */
/*   Updated: 2022/01/13 11:53:37 by fmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interrupt(int num)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	interrupt_cmd(int num)
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signals2(void)
{
	signal(SIGINT, interrupt_cmd);
	signal(SIGQUIT, SIG_IGN);
}

void	signals(void)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, SIG_IGN);
}
