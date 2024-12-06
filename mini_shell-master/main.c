/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:11:11 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 12:52:35 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	leaks(void)
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini_shell	ms;
	char			*txt;

	argv = NULL;
	copy_envp(envp, &ms);
	ms.status = 0;
	signal(SIGQUIT, int_handler);
	signal(SIGINT, int_handler);
	if (argc > 1)
		return (printf("🐦‍🔥minishell> Too many arguments\n"), 1);
	while (1)
	{
		g_id_signal = 0;
		txt = readline("🐦‍🔥minishell> ");
		if (!txt)
			break ;
		if (*txt != '\0')
		{
			add_history(txt);
			find_lines(txt, &ms);
		}
		else
			free (txt);
	}
	exit (0);
}
