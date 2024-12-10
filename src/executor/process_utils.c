/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:10:06 by miparis           #+#    #+#             */
/*   Updated: 2024/12/10 10:24:57 by miparis          ###   ########.fr       */
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