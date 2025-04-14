/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:25:13 by codespace         #+#    #+#             */
/*   Updated: 2025/02/09 21:44:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(name, envp[i], ft_strlen(name)) == 0)
			return (envp[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

void	update_env(char *value, char **envp)
{
	if (ft_strncmp("PWD=", *envp, 4) == 0)
	{
		free(*envp);
		*envp = ft_strjoin("PWD=", value);
	}
	else if (ft_strncmp("OLDPWD=", *envp, 7) == 0)
	{
		free(*envp);
		*envp = ft_strjoin("OLDPWD=", value);
	}
}

int	update_pwd(char **envp, t_mini *mini)
{
	char	pwd[PATH_MAX];
	int		i;
	char	*oldpwd;

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("cd");
		mini->last_status = 1;
		return (1);
	}
	i = 0;
	oldpwd = ft_getenv("PWD", envp);
	if (!oldpwd)
		oldpwd = ft_strdup("\0");
	else
		oldpwd = ft_strdup(oldpwd);
	while (envp[i])
	{
		if (ft_strncmp("OLDPWD=", envp[i], 7) == 0)
			update_env(oldpwd, &envp[i]);
		else if (ft_strncmp("PWD=", envp[i], 4) == 0)
			update_env(pwd, &envp[i]);
		i++;
	}
	return (free(oldpwd), 0);
}

int	cd_home(char **envp, t_mini *mini)
{
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		mini->last_status = 1;
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		mini->last_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_cmd *cmd, char **envp, t_mini *mini)
{
	if (!cmd->args[1] || (ft_strcmp(cmd->args[1], "~") == 0))
	{
		if (cd_home(envp, mini))
			return ;
	}
	else
	{
		if (ft_strcmp(cmd->args[1], "-") == 0)
		{
			if (cd_hyphen(mini->envp, mini))
				return ;
		}
		else if (chdir(cmd->args[1]) == -1)
		{
			write(2, "MINICHONCHAA: cd: ", 18);
			write(2, cmd->args[1], ft_strlen(cmd->args[1]));
			write(2, ": Cannot open that file or directory\n", 38);
			mini->last_status = 1;
			return ;
		}
	}
	update_pwd(envp, mini);
}
