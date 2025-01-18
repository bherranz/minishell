/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:10:06 by miparis           #+#    #+#             */
/*   Updated: 2025/01/18 16:53:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Problem creating process\n");
		exit(1);
	}
	else
		return (pid);
}

void	set_struct(t_pipe *t_struct)
{
	t_struct->last_pid = 0;
	t_struct->cmds_num = 0;
	t_struct->cmd_index = 0;
	t_struct->old_pipe[0] = 0;
	t_struct->old_pipe[1] = 0;
	t_struct->new_pipe[0] = 0;
	t_struct->new_pipe[1] = 0;
}

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

void	create_pipe(t_pipe *pipes)
{
	if (pipe(pipes->new_pipe) < 0)
	{
		print_error("Error: Problem with pipe", "", 0, -1);
		exit (-1);
	}
}

void	close_pipe_struct(t_pipe *pipes)
{
	if (pipes->old_pipe[0])
		close(pipes->old_pipe[0]);
	if (pipes->old_pipe[1])
		close(pipes->old_pipe[1]);
	if (pipes->new_pipe[0])
		close(pipes->new_pipe[0]);
	if (pipes->new_pipe[1])
		close(pipes->new_pipe[1]);
}
