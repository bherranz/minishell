/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 05:02:34 by codespace         #+#    #+#             */
/*   Updated: 2025/01/19 11:14:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	new_input(t_mini *mini)
{
	char	*input;
	int		i;

	input = readline("MINICONCHAA > ");
	if (!input)
	{
		printf("exit\n");
		if (mini->envp)
			free_array(mini->envp);
		rl_clear_history();
		close_std_fd(mini);
		free_structs(mini);
		return (1);
	}
	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	mini->input = ft_substr(input, i, ft_strlen(input));
	free(input);
	return (0);
}

void	print_error(char *msg, char *var, int perr, int err)
{
	if (perr)
		perror(msg);
	else
		ft_putendl_fd(msg, var, 2);
	(void)err;
}
