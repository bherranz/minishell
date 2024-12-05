/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:13:39 by codespace         #+#    #+#             */
/*   Updated: 2024/12/05 07:45:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	index_envp(char **envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**rm_var(char **envp, int idx)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)calloc(sizeof(char *), i); //no se suma 1 para el NULL porque se va a restar un elemento
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != idx)
		{
			new_envp[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	return (new_envp);
}

void	ft_unset(t_mini *mini, char **var)
{
	int		i;
	int		idx;
	char	**temp;

	i = 1;
	while (var[i])
	{
		idx = index_envp(mini->envp, var[i]);
		if (idx >= 0)
		{
			temp = mini->envp;
			mini->envp = rm_var(mini->envp, idx);
			free_array(temp);
		}
		i++;
	}
}
