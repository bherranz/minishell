/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:25:13 by codespace         #+#    #+#             */
/*   Updated: 2024/12/03 02:46:39 by codespace        ###   ########.fr       */
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

int	update_env(char *value, char **envp)
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
	return (1);
}

int	update_pwd(char **envp)
{
	char	pwd[PATH_MAX];
	int		i;

	if (!getcwd(pwd, sizeof(pwd)))
	{
		perror("cd");
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("OLDPWD=", envp[i], 7) == 0)
			update_env(ft_getenv("PWD", envp), &envp[i]);
		else if (ft_strncmp("PWD=", envp[i], 4) == 0)
			update_env(pwd, &envp[i]);
		i++;
	}
	return (0);
}

int	cd_home(char **envp)
{
	char	*home;

	home = ft_getenv("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, char **envp)
{
	if (!cmd->args[1]) //only cd
	{
		if (cd_home(envp))
			return (1);
	}
	else
	{
		if (chdir(cmd->args[1]) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	if (update_pwd(envp))
		return (1);
	printf("PWD: %s\n", ft_getenv("PWD", envp));
	printf("OLDPWD: %s\n", ft_getenv("OLDPWD", envp));
	return (0);
}
