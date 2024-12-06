/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:06 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 10:49:12 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	int_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_id_signal)
			write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_id_signal)
			rl_redisplay();
	}
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
	exit(0);
}
