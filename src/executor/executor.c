/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:47:28 by miparis           #+#    #+#             */
/*   Updated: 2025/01/07 12:20:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executor(t_mini *mini)
{
	t_pipe		*pipes;
	int			i;

	pipes = malloc(sizeof(*pipes));
	set_struct(pipes);
	if (control(pipes))
			return (-1);
	i = 0;
	while (i < (mini->pipes + 1) && mini->cmd[i])
	{
		if (open_files(mini->cmd[i]))
			return (-1);
		if (mini->pipes == 0)
		{
			printf("---> Single process...\n");
			one_cmd(mini->cmd[0], mini);
		}
		else
			multiple_processes(mini->cmd[i], mini, pipes);
		i++;
		process_status(pipes, mini);
	}
	close_pipe_struct(pipes);
	//close(pipes->old_pipe[READ]);
	free(pipes);
	return (0);
}

void process_status(t_pipe *pipes, t_mini *mini)
{
	int		status;
	pid_t	current_child;
	
	while (1)
	{
		current_child = waitpid(-1, &status, 0);
		if (current_child <= 0)
			break;
		if (current_child == pipes->last_pid)
			mini->last_status = WEXITSTATUS(status);
	}
}
