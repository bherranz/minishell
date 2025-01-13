/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:47:28 by miparis           #+#    #+#             */
/*   Updated: 2025/01/13 18:29:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executor(t_mini *mini)
{
	t_pipe		*pipes;
	int			i;

	pipes = malloc(sizeof(*pipes));
	set_struct(pipes);
	if (control(pipes))
			return ;
	i = 0;
	while (i < (mini->pipes + 1) && mini->cmd[i])
	{
		if (mini->pipes == 0)
		{
			printf("---> Single process...\n");
			if (open_files(mini->cmd[0], mini))
				break ;
			one_cmd(mini->cmd[0], mini);
		}
		else
			multiple_processes(mini->cmd[i], mini, pipes);
		i++;
	}
	process_status(pipes, mini);
	close_pipe_struct(pipes);
	free(pipes);
}

void	process_status(t_pipe *pipes, t_mini *mini)
{
	int		status;
	pid_t	current_child;

	while ((current_child = waitpid(-1, &status, 0)) != -1)
	{
		if (current_child > 0)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					mini->last_status = 130;
				if (WTERMSIG(status) == SIGQUIT)
				{
					mini->last_status = 131;
					if (current_child == pipes->last_pid)
						write(STDERR_FILENO, "Quit (core dumped)\n", 20);
				}
			}
			else if (WIFEXITED(status))
			{
				mini->last_status = WEXITSTATUS(status);
			}
		}
	}
}
