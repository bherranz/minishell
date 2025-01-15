/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:35:50 by codespace         #+#    #+#             */
/*   Updated: 2025/01/14 16:26:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	sigint_here_doc(int sig)
{
	(void)sig;
	exit(130);
}

void	signals_here_doc(void)
{
	signal(SIGINT, sigint_here_doc);
}
