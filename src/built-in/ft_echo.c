/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:46:40 by codespace         #+#    #+#             */
/*   Updated: 2025/01/11 11:58:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_nflag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		i++;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && check_nflag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	mini->last_status = 0;
}
