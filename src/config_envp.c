/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:04:56 by codespace         #+#    #+#             */
/*   Updated: 2025/02/10 17:25:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_flags(char **envp, int *shlvl, int *pwd, int *user)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
			*shlvl = 1;
		if (!ft_strncmp(envp[i], "PWD=", 4))
			*pwd = 1;
		if (!ft_strncmp(envp[i], "USER=", 5))
			*user = 1;
		i++;
	}
}

void	fill_missing_vars(t_mini *mini, int pwd, int shlvl, int user)
{
	char	**aux;
	char	*temp;

	aux = (char **)ft_calloc(4, sizeof(char *));
	aux[0] = ft_strdup("export");
	if (pwd == 0)
	{
		temp = getcwd(NULL, 0);
		aux[1] = ft_strjoin("PWD=", temp);
		ft_export(mini, aux);
		free(temp);
	}
	if (shlvl == 0)
	{
		free(aux[1]);
		aux[1] = ft_strdup("SHLVL=1");
		ft_export(mini, aux);
	}
	if (user == 0)
	{
		free(aux[1]);
		aux[1] = ft_strdup("USER=/usr/bin/env");
		ft_export(mini, aux);
	}
	free_array(aux);
}

void	basic_config(t_mini *mini)
{
	int	shlvl;
	int	pwd;
	int	user;

	shlvl = 0;
	pwd = 0;
	user = 0;
	set_flags(mini->envp, &shlvl, &pwd, &user);
	fill_missing_vars(mini, pwd, shlvl, user);
}

void	set_envp(t_mini *mini, char **envp)
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
		if (!strncmp(envp[i], "SHLVL=", 6))
			new[i] = shell_level(envp[i], 1);
		else
			new[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->envp = new;
	basic_config(mini);
}
