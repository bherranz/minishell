/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2025/01/19 12:21:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

void	process_commands(t_mini *mini)
{
	if (parser(mini))
	{
		mini->last_status = 1;
		free_structs(mini);
	}
	else
	{
		executor(mini);
		free_structs(mini);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	set_envp(&mini, envp);
	(void)argc;
	(void)argv;
	g_signal = 0;
	signals_handler();
	while (1)
	{
		init_mini(&mini);
		if (new_input(&mini))
			break ;
		if (mini.input[0] != '\0')
			add_history(mini.input);
		if (mini.input[0] == '\0')
			free(mini.input);
		else
			process_commands(&mini);
	}
	return (0);
}
