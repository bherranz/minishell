/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:23 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 15:27:13 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	do_first_child(t_mini_shell *ms)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
		manage_fd_in(&fd_in, ms, 0);
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	if (exec_builtin(ms->cmds[0].cmd, ms) == 0)
		exit (0);
	find_path(ms, 0);
	if (ms->cmds[0].awk)
		execve(ms->cmds[0].path, do_awk(ms, 0), ms->envp);
	else if (!strchr(ms->cmds[0].cmd, '|'))
		execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}

static void	close_mid_child(t_mini_shell *ms)
{
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
}

void	do_middle_child(t_mini_shell *ms, int ci)
{
	int	fd_in;
	int	fd_out;

	if (ms->cmds[ci].infiles[0] || ms->cmds[ci].here_doc)
		manage_fd_in(&fd_in, ms, ci);
	else
		dup2(ms->old_tubes[0], 0);
	if (ms->cmds[ci].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, ci);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close_mid_child(ms);
	if (exec_builtin(ms->cmds[0].cmd, ms) == 0)
		exit (0);
	find_path(ms, ci);
	if (ms->cmds[ci].awk)
		execve(ms->cmds[ci].path, do_awk(ms, ci), ms->envp);
	else if (!strchr(ms->cmds[ci].cmd, '|'))
		execve(ms->cmds[ci].path, ft_split(ms->cmds[ci].cmd, ' '), ms->envp);
	exit_child(ms);
}

void	do_last_child(t_mini_shell *ms, int ci)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[ci].infiles[0] != NULL || ms->cmds[ci].here_doc == 1)
		manage_fd_in(&fd_in, ms, ci);
	else
		dup2(ms->new_tubes[0], 0);
	if (ms->cmds[ci].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, ci);
		dup2(fd_out, 1);
		close(fd_out);
	}
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	if (exec_builtin(ms->cmds[0].cmd, ms) == 0)
		exit (0);
	find_path(ms, ci);
	if (ms->cmds[ci].awk)
		execve(ms->cmds[ci].path, do_awk(ms, ci), ms->envp);
	else if (!strchr(ms->cmds[ci].cmd, '|'))
		execve(ms->cmds[ci].path, ft_split(ms->cmds[ci].cmd, ' '), ms->envp);
	exit_child(ms);
}
