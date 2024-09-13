/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bherranz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/13 12:26:01 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	mini.envp = envp;
	//solo era para compilar
	(void)mini;
	(void)argc;
	(void)argv;
	//meter el readline
	while (1)
	{
		char *input = readline("MINICONCHAA > ");
		if (input && *input)
		    add_history(input);
		else
			(void)input;
	}
	return (0);
}
