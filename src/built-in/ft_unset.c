/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 04:13:39 by codespace         #+#    #+#             */
/*   Updated: 2025/02/10 15:28:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_unset(char *var, t_mini *mini)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	mini->last_status = 1;
}

int	check_var_unset(char *var, t_mini *mini)
{
	int		i;

	i = 0;
	if ((!ft_isalpha(var[i]) && var[i] != '_') || !var[i])
		return (error_unset(var, mini), 0);
	i++;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (error_unset(var, mini), 0);
		i++;
	}
	if (ft_strcmp(var, "_") == 0)
		return (0);
	return (1);
}

int	index_envp(char **envp, char *var, t_mini *mini)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	if (check_var_unset(var, mini) == 0)
		return (-1);
	if (ft_strncmp(var, "SHLVL", 5) == 0)
		return (unset_shlvl(envp), -1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len))
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
	new_envp = (char **)calloc(sizeof(char *), i);
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
		idx = index_envp(mini->envp, var[i], mini);
		if (idx >= 0)
		{
			temp = mini->envp;
			mini->envp = rm_var(mini->envp, idx);
			free_array(temp);
		}
		i++;
	}
}
