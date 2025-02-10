/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 03:55:45 by codespace         #+#    #+#             */
/*   Updated: 2025/02/10 16:57:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(char **envp, t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		ft_putstr_fd("MINICONCHAA > env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		mini->last_status = 127;
		return ;
	}
	mini->last_status = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			env_print_shlvl(envp[i]);
		else if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
}
