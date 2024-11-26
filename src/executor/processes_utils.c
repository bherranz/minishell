/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:10:06 by miparis           #+#    #+#             */
/*   Updated: 2024/11/26 10:03:11 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_struct(t_struct *t_struct, char *argv[])
{
	t_struct->is_here_doc = false;
	t_struct->infile = -1;
	t_struct->outfile = -1;
	t_struct->cmds_num = 0;
	t_struct->cmd_index = 0;
	t_struct->arguments = NULL;
	t_struct->argv = argv;
	t_struct->old_pipe[0] = 0;
	t_struct->old_pipe[1] = 0;
	t_struct->new_pipe[0] = 0;
	t_struct->new_pipe[1] = 0;
}

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
}

void	control(t_struct *t_struct)
{
	if (pipe(t_struct->old_pipe) == -1)
	{
		perror("Problem creating pipe\n");
		close(t_struct->new_pipe[WRITE]);
		close(t_struct->new_pipe[READ]);
		free(t_struct);
		exit(1);
	}
	if (t_struct->infile == -1)
	{
		perror(t_struct->argv[1]);
		close(t_struct->old_pipe[WRITE]);
		free(t_struct);
		exit(1);
	}
}
