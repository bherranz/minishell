/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:14:04 by codespace         #+#    #+#             */
/*   Updated: 2025/01/18 16:16:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_nb(char *var)
{
	int	i;

	i = 0;
	if (var[0] == '-')
		i++;
	while (var[i])
	{
		if (!ft_isdigit(var[i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		i++;
	}
}

void	do_exit(t_mini *mini, int status)
{
	printf("exit\n");
	rl_clear_history();
	close_pipe_struct(mini->pipes);
	close_std_fd(mini);
	free_structs(mini);
	exit(status);
}

void	ft_exit(t_mini *mini, char **var)
{
	int	nb;

	if (!var[1])
		do_exit(mini, mini->last_status);
	check_nb(var[1]);
	if (var[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		mini->last_status = 1;
		return ;
	}
	nb = ft_atoi(var[1]);
	do_exit(mini, nb % 256);
}
