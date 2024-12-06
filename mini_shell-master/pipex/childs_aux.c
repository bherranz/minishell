/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:26 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:27 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	exit_child(t_mini_shell *ms)
{
	perror("error");
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	exit(127);
}

void	manage_fd_in(int *fd_in, t_mini_shell *ms, int child_index)
{
	*fd_in = open_infiles(ms, child_index);
	if (ms->cmds[child_index].here_doc == 1)
	{
		*fd_in = ms->cmds[child_index].tuvo[0];
		dup2(*fd_in, 0);
		close(ms->cmds[child_index].tuvo[1]);
	}
	else
		dup2(*fd_in, 0);
	close(*fd_in);
}

int	open_infiles(t_mini_shell *ms, int index)
{
	int	i;
	int	fd;

	i = 0;
	while (ms->cmds[index].infiles[i])
	{
		fd = open(ms->cmds[index].infiles[i], O_RDONLY);
		if (fd == -1)
			exit_child(ms);
		close(fd);
		i++;
	}
	if (ms->cmds[index].here_doc == 0)
		fd = open(ms->cmds[index].infiles[i - 1], O_RDONLY);
	return (fd);
}

int	open_outfiles(t_mini_shell *ms, int index)
{
	int	i;
	int	fd;

	i = 0;
	while (ms->cmds[index].outfiles[i] && ms->cmds[index].outfiles[i + 1])
	{
		fd = open(ms->cmds[index].outfiles[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			exit_child(ms);
		close(fd);
		i++;
	}
	if (ms->cmds[index].trunc == 1)
		fd = open(ms->cmds[index].outfiles[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(ms->cmds[index].outfiles[i], \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}
