/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:47:28 by miparis           #+#    #+#             */
/*   Updated: 2025/01/18 16:57:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_here_docs(t_cmd *cmd, t_mini *mini)
{
	t_io_file	*current;

	current = cmd->infile;
	while (current)
	{
		if (current->type == 2)
		{
			if (process_here_doc(current, mini))
				return (-1);
			if (fd_control(current, mini))
				return (-1);
			unlink("/tmp/temp_file");
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

void	executor(t_mini *mini)
{
	int			i;

	mini->pipes = malloc(sizeof(*(mini->pipes)));
	if (!mini->pipes)
		return (print_error("Error: malloc", "", 0, -1));
	set_struct(mini->pipes);
	if (control(mini->pipes))
		return (free_structs(mini));
	i = 0;
	while (i < (mini->pipes_n + 1) && mini->cmd[i])
		if (process_here_docs(mini->cmd[i++], mini))
			return ;
	i = 0;
	while (i < (mini->pipes_n + 1) && mini->cmd[i])
	{
		if (mini->pipes_n == 0)
			one_cmd(mini->cmd[0], mini);
		else
			multiple_processes(mini->cmd[i], mini, mini->pipes);
		i++;
	}
	process_status(mini->pipes, mini);
	close_pipe_struct(mini->pipes);
}

void	process_status(t_pipe *pipes, t_mini *mini)
{
	int		status;
	pid_t	current_child;

	(void)pipes;
	current_child = waitpid(-1, &status, 0);
	while (current_child != -1)
	{
		current_child = waitpid(-1, &status, 0);
		if (current_child > 0)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					mini->last_status = 130;
				else if (WTERMSIG(status) == SIGQUIT)
					mini->last_status = 131;
			}
			if (WIFEXITED(status))
				mini->last_status = WEXITSTATUS(status);
		}
	}
}
