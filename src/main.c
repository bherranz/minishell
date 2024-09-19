/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/19 08:19:38 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Ctrl + C
void sigint_handler(int sig)
{
    (void)sig;  // Para evitar advertencias
    printf("\n");
    rl_on_new_line();    // Marca que hay una nueva línea
    rl_replace_line("", 0); // Borra la línea actual en readline
    rl_redisplay();      // Redibuja el prompt
}

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
		signal(SIGINT, sigint_handler);
		char *input = readline("MINICONCHAA > ");
		if (input && *input)
		    add_history(input);
		else
			(void)input;
		if (ft_strcmp(input, "exit") == 0)
			break;
	}
	return (0);
}
