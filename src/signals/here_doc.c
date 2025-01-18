/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:35:50 by codespace         #+#    #+#             */
/*   Updated: 2025/01/18 16:44:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_here_doc(int sig)
{
	(void)sig;
	g_signal = 130;
	exit(128 + SIGINT);
}

void	signals_here_doc(void)
{
	signal(SIGINT, sigint_here_doc);
}
