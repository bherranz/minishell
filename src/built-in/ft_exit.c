/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:14:04 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 13:29:03 by codespace        ###   ########.fr       */
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

void	ft_exit(t_mini *mini, char **var)
{
	int	nb;

	mini->last_status = 0;
	if (!var[1])
		exit(mini->last_status);
	check_nb(var[1]);
	if (var[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		mini->last_status = 1;
		return ;
	}
	printf("exit\n");
	nb = ft_atoi(var[1]);
	mini->last_status = nb % 256;
	exit(mini->last_status);
}
