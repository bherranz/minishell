/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:15 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 15:23:54 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	open_files(int *fd_in, t_mini_shell *ms)
{
	*fd_in = open_infiles(ms, 0);
	if (ms->cmds[0].here_doc == 1)
	{
		*fd_in = ms->cmds[0].tuvo[0];
		dup2(*fd_in, 0);
		close(ms->cmds[0].tuvo[1]);
	}
	else
		dup2(*fd_in, 0);
	close(*fd_in);
}

char	**alloc_awk(char **strs, t_mini_shell *ms, int child_index)
{
	char	**sol;
	int		i;

	i = 0;
	while (ms->cmds[child_index].infiles[i])
		i++;
	sol = malloc(sizeof(char *) * 4);
	sol[0] = ft_strdup(strs[0]);
	sol[1] = ft_strdup(strs[1]);
	sol[2] = ft_strdup(ms->cmds[child_index].infiles[i - 1]);
	sol[3] = NULL;
	free_strs(strs);
	return (sol);
}

char	**do_awk(t_mini_shell *ms, int child_index)
{
	char	**sol;
	int		i;
	char	*aux;

	i = 0;
	sol = ft_split(ms->cmds[child_index].cmd, '\'');
	skip_spaces(sol[0], &i);
	aux = sol[0];
	sol[0] = ft_substr(sol[0], i, ft_strlen(sol[0]));
	free(aux);
	if (sol[2])
	{
		i = 0;
		skip_spaces(sol[2], &i);
		aux = sol[2];
		sol[2] = ft_substr(sol[2], i, ft_strlen(sol[2]));
		free(aux);
	}
	if (!(ms->cmds[child_index].infiles[0] != NULL || \
		ms->cmds[child_index].here_doc == 1))
		return (sol);
	return (alloc_awk(sol, ms, child_index));
}

void	do_one_child(t_mini_shell *ms)
{
	int		fd_in;
	int		fd_out;
	int		i;

	i = 0;
	fd_in = 0;
	fd_out = 0;

	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
		open_files(&fd_in, ms);
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (exec_builtin(ms->cmds[0].cmd, ms) == 0)
		exit (0);
	find_path(ms, 0);
	if (ms->cmds[0].awk)
		execve(ms->cmds[0].path, do_awk(ms, 0), ms->envp);
	else if (!strchr(ms->cmds[0].cmd, '|'))
		execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}
