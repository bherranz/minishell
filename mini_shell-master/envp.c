/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:03 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:04 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	check_basics(t_mini_shell *ms, int *pwd, int *shlvl, int *user)
{
	int	i;

	i = 0;
	while (ms->envp[i] != 0)
	{
		if (!ft_strncmp(ms->envp[i], "PWD=", 4))
			*pwd = 1;
		if (!ft_strncmp(ms->envp[i], "SHLVL=", 6))
			*shlvl = 1;
		if (!ft_strncmp(ms->envp[i], "_=", 2))
			*user = 1;
		i++;
	}
}

static void	set_basics(t_mini_shell *ms)
{
	int		pwd;
	int		shlvl;
	int		user;
	char	*rute;
	char	*aux;

	pwd = 0;
	shlvl = 0;
	user = 0;
	check_basics(ms, &pwd, &shlvl, &user);
	rute = getcwd(NULL, 0);
	if (pwd == 0)
	{
		aux = ft_strjoin("export PWD=", rute);
		do_export(aux, ms);
		free(aux);
	}
	if (rute)
		free (rute);
	if (shlvl == 0)
		do_export("export SHLVL=1", ms);
	if (user == 0)
		do_export("export _=/usr/bin/env", ms);
}

static char	*do_shell_lvl(char *line)
{
	char	**strs;
	int		num;
	char	*sol;
	char	*aux;

	strs = ft_split(line, '=');
	if (strs[2])
		return (ft_strdup("SHLVL=1"));
	num = 0;
	while (strs[1][num])
	{
		if (!ft_isdigit(strs[1][num]))
			return (ft_strdup("SHLVL=1"));
		num++;
	}
	num = ft_atoi(strs[1]);
	num++;
	aux = ft_itoa(num);
	sol = ft_strjoin("SHLVL=", aux);
	free(aux);
	free_strs(strs);
	return (sol);
}

void	copy_envp(char **envp, t_mini_shell *ms)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	ms->envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ms->envp)
		return ;
	ms->envp[len] = NULL;
	len = 0;
	while (envp[len])
	{
		if (!(ft_strncmp(envp[len], "SHLVL=", 6)))
			ms->envp[len] = do_shell_lvl(envp[len]);
		else
			ms->envp[len] = ft_strdup(envp[len]);
		len++;
	}
	set_basics(ms);
}
