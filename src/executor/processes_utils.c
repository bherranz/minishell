/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:10:06 by miparis           #+#    #+#             */
/*   Updated: 2024/11/27 13:19:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_struct(t_pipe *t_struct)
{
	t_struct->cmds_num = 0;
	t_struct->cmd_index = 0;
	t_struct->old_pipe[0] = 0;
	t_struct->old_pipe[1] = 0;
	t_struct->new_pipe[0] = 0;
	t_struct->new_pipe[1] = 0;
}
/*
void	set_cmds_num(t_struct *t_struct, int argc)
{
	if (t_struct->is_here_doc)
		t_struct->cmds_num = argc - 4;
	else
		t_struct->cmds_num = argc - 3;
	if (t_struct->is_here_doc == true)
		t_struct->cmd_index = 3;
	else
		t_struct->cmd_index = 2;
}*/

int	control(t_pipe *pipes)
{
	if (pipe(pipes->old_pipe) == -1)
	{
		perror("Problem creating pipe\n");
		close(pipes->new_pipe[WRITE]);
		close(pipes->new_pipe[READ]);
		free(pipes);
		return (1);
	}
	return (0);
}
