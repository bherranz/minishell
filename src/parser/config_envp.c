/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:04:56 by codespace         #+#    #+#             */
/*   Updated: 2024/12/04 05:01:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	while (envp[i])
		i++;
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new);
}

void	set_envp(t_mini *mini, char **envp)
{
	mini->envp = copy_envp(envp);
}

