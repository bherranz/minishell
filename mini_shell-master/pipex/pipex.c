/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:13 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:14 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	close_parent(t_mini_shell *ms)
{
	int	i;

	i = 0;
	while (ms->childs[i] != -1)
	{
		waitpid(ms->childs[i], &(ms->status), 0);
		++i;
	}
}

void	pipex(t_mini_shell *ms)
{
	ms->childs = malloc(sizeof(pid_t *) * (ms->num_cmds + 1));
	ms->childs[ms->num_cmds] = -1;
	if (ms->childs == NULL)
		exit (1);
	if (do_forks(ms) == 1)
		exit(1);
	close (ms->new_tubes[0]);
	close_parent(ms);
	free(ms->childs);
	exit(WEXITSTATUS(ms->status));
}
