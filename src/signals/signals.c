/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:52:24 by miparis           #+#    #+#             */
/*   Updated: 2025/01/19 11:08:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Ctrl + C
void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_signal == 2)
		return ;
	else if (g_signal != 0)
	{
		g_signal = 130;
		write(1, "\n", 1);
	}
}

void	signals_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
