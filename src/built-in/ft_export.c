/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 02:47:51 by codespace         #+#    #+#             */
/*   Updated: 2024/12/06 05:44:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	order_envp(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (envp[i])
		printf("declare -x \"%s\"\n", envp[i++]);
}

int	is_in_envp(char **envp, char *var)
{
	int		i;
	char	**temp;
	char	**e_temp;

	i = 0;
	while (envp[i])
	{
		temp = ft_split(var, '=');
		if (!temp || !temp[0])
			return (free_array(temp), -1);
		if (ft_strchr(var, '='))
		{
			e_temp = ft_split(envp[i], '=');
			if (!e_temp || !e_temp[0])
				return (free_array(temp), free_array(e_temp), -1);
			if (ft_strcmp(e_temp[0], temp[0]) == 0)
				return (free_array(temp), free_array(e_temp), i);
			free_array(e_temp);
		}
		free_array(temp);
		i++;
	}
	return (-1);
}

char	**add_new_vars(char **new, char **var, int i, t_mini *mini)
{
	int		j;
	int		idx;

	j = 0;
	while (var[j])
	{
		if (ft_strchr(var[j], '=') && ft_isalpha(var[j][0]))
		{
			idx = is_in_envp(mini->envp, var[j]);
			if (idx < 0)
			{
				new[i] = ft_strdup(var[j]);
				i++;
			}
			else
			{
				free(new[idx]);
				new[idx] = ft_strdup(var[j]);
			}
		}
		j++;
	}
	return (new);
}

char	**new_envp(int count, t_mini *mini, char **var)
{
	int		i;
	char	**new;

	i = 0;
	while (mini->envp[i])
		i++;
	new = (char **)ft_calloc(i + count + 1, sizeof(char *));
	i = 0;
	while (mini->envp[i])
	{
		new[i] = ft_strdup(mini->envp[i]);
		i++;
	}
	add_new_vars(new, var, i, mini);
	free_array(mini->envp);
	return (new);
}

void	ft_export(t_mini *mini, char **var)
{
	int		i;
	int		new;
	char	**temp;

	i = 0;
	if (!var[1]) //export sin opciones
	{
		order_envp(mini->envp);
		return ;
	}
	new = 0;
	while (var[i])
	{
		temp = ft_split(var[i], '=');
		if (ft_strchr(var[i], '='))
		{
			if (*temp && is_in_envp(mini->envp, temp[0]))
				new++;
		}
		free_array(temp);
		i++;
	}
	mini->envp = new_envp(new, mini, var);
}
