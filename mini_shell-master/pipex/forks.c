/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:18 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 15:03:35 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	first_fork(t_mini_shell *ms)
{
	ms->childs[0] = fork();
	if (ms->childs[0] == -1)
		return (1);
	if (ms->childs[0] == 0)
		do_first_child(ms);
	return (0);
}

static int	loop_fork(t_mini_shell *ms, int child_index)
{
	ms->old_tubes[0] = ms->new_tubes[0];
	ms->old_tubes[1] = ms->new_tubes[1];
	if (pipe(ms->new_tubes) == -1)
		return (1);
	ms->childs[child_index] = fork();
	if (ms->childs[child_index] == -1)
		return (1);
	if (ms->childs[child_index] == 0)
		do_middle_child(ms, child_index);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	return (0);
}

static int	last_fork(t_mini_shell *ms, int child_index)
{
	ms->childs[child_index] = fork();
	if (ms->childs[child_index] == -1)
		return (1);
	if (ms->childs[child_index] == 0)
		do_last_child(ms, child_index);
	return (0);
}

static int	one_fork(t_mini_shell *ms)
{
	ms->childs[0] = fork();
	if (ms->childs[0] == -1)
		return (1);
	if (ms->childs[0] == 0)
		do_one_child(ms);
	return (0);
}

int	do_forks(t_mini_shell *ms)
{
	int		child_index;

	if (ms->num_cmds > 1)
	{
		child_index = 1;
		if (pipe(ms->new_tubes) == -1)
			return (1);
		if (first_fork(ms) == 1)
			return (1);
		while (child_index <= ms->num_cmds - 2)
		{
			if (loop_fork(ms, child_index) == 1)
				return (1);
			++child_index;
		}
		if (last_fork(ms, child_index) == 1)
			return (1);
		close(ms->new_tubes[0]);
		close(ms->new_tubes[1]);
		return (0);
	}
	else
		return (one_fork(ms));
}
