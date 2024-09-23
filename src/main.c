/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/23 10:33:32 by miparis          ###   ########.fr       */
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
	//meter el readline
	g_signal = 0;
	signals_handler();
	while (1)
	{
		mini.input = readline("MINICONCHAA > ");
		if (mini.input == NULL) //agregado por seg fault al hacer cltr D
		{
			printf("\nQuiting progam...\n");
			break;
		}
		if (mini.input)
		    add_history(mini.input);
		else
			(void)mini.input;
		if (ft_strcmp(mini.input, "exit") == 0)
			break;
		free(mini.input);
	}
	return (0);
}
