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
	(void)sig; // Para evitar advertencias
	if (g_signal == 0) //modo interactivo, esperando por un prompt
	{
		write(1, "\n", 1);
		rl_on_new_line(); // Marca que hay una nueva línea
		rl_replace_line("", 0); // Borra la línea actual en readline
		rl_redisplay();
	}
	if (g_signal == 2) //procesos en segundo plano, no debe interrumpir nada
		return ;
	else if (g_signal != 0)
	{
		g_signal = 130; // se establece signal a 130, còdigo de salida en casos de SIGINT
		write(1, "\n", 1);
	}
}

void	signals_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
