/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:46:13 by miparis           #+#    #+#             */
/*   Updated: 2024/12/09 10:49:02 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path(char *command, char *envp[])
{
	char	**paths;
	char	*path;
	char	*command_path;
	int		i;

	i = -1;
	if (ft_strchr(command, '/'))
		return (command);
	paths = retrieve_paths(envp);
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (ft_free(paths), NULL);
		command_path = ft_strjoin(path, command);
		free(path);
		if (!command_path)
			return (ft_free(paths), NULL);
		if (access(command_path, X_OK) == 0)
			return (ft_free(paths), command_path);
		free(command_path);
	}
	return (ft_free(paths), NULL);
}

char	**retrieve_paths(char *envp[])
{
	char	*path;
	char	**paths;

	path = get_env_path("PATH", envp);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

char	*get_env_path(char *path, char *envp[])
{
	int		i;
	size_t	p_len;

	i = 0;
	p_len = ft_strlen(path);
	while (envp[i])
	{
		if (ft_strncmp(path, envp[i], p_len) == 0)
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}
