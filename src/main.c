/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/24 05:56:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.envp = envp;
	(void)argc;
	(void)argv;
	g_signal = 0;
	signals_handler();
	while (1)
	{
		mini.input = readline("MINICONCHAA > ");
		if (mini.input == NULL) //agregado por seg fault al hacer cltr D
		{
			printf("\nQuiting progam...\n");
			break ;
		}
		if (mini.input)
			add_history(mini.input);
		// esto sirve para algo?
		// else
		// 	(void)mini.input;
		if (ft_strcmp(mini.input, "exit") == 0)
			break ;
		parser(&mini);
		free(mini.input);
	}
	return (0);
}
