/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:10 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:11 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_rutes(char **rutes)
{
	int	i;

	i = 0;
	while (rutes[i])
	{
		free(rutes[i]);
		++i;
	}
	free(rutes);
}

char	**get_paths(t_mini_shell *ms)
{
	int		i;
	char	*aux;
	char	**rutes;

	i = 0;
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], "PATH", 4) == 0)
		{
			aux = ft_substr(ms->envp[i], 5, ft_strlen(ms->envp[i]) - 5);
			rutes = ft_split(aux, ':');
			free(aux);
			return (rutes);
		}
		++i;
	}
	return (NULL);
}

int	check_rute(char *rute, t_mini_shell *ms, int cmd_i)
{
	char	*aux;
	char	*cmd;
	char	**split_cmd;

	split_cmd = ft_split(ms->cmds[cmd_i].cmd, ' ');
	aux = ft_strjoin(rute, "/");
	cmd = ft_strjoin(aux, split_cmd[0]);
	free(aux);
	if (access(cmd, X_OK) == 0)
	{
		ms->cmds[cmd_i].path = cmd;
		return (0);
	}
	free(cmd);
	return (1);
}
//free¿?

void	find_path(t_mini_shell *ms, int cmd_i)
{
	int		i;
	char	**rutes;
	char	**cmd;

	cmd = ft_split(ms->cmds[cmd_i].cmd, ' ');
	rutes = get_paths(ms);
	if (!rutes)
	{
		ms->cmds[cmd_i].path = cmd[0];
		return ;
	}
	i = 0;
	while (rutes[i])
	{
		if (check_rute(rutes[i], ms, cmd_i) == 0)
			return (free_rutes(rutes));
		++i;
	}
	ms->cmds[cmd_i].path = cmd[0];
	free_rutes(rutes);
}
