/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:49:59 by miparis           #+#    #+#             */
/*   Updated: 2025/01/12 23:13:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds(t_io_file *fds)
{
	t_io_file	*current;

	current = fds;
	while (current)
	{
		if (current->fd > -1)
			close(current->fd);
		current = current->next;
	}
}

void	redir_pipe(int pipe_fd, int type, t_io_file *current)
{
	if (pipe_fd >= 0 && !current)
	{
		if (dup2(pipe_fd, type) == -1)
		{
			print_error("Error: dup2", "", 0, -1);
			exit(-1);
		}
	}
}

void	replace_dup2(t_io_file *fds, int pipe_fd, int type, t_mini *mini)
{
	t_io_file	*current;

	current = fds;
	while (current)
	{
		if (current->last_in)
		{
			if (dup2(current->fd, type) == -1)
			{
				print_error("Error: dup2", "", 0, -1);
				close_fds(fds);
				mini->last_status = 1;
				exit(mini->last_status);
			}
			break ;
		}
		close(current->fd);
		current = current->next;
	}
	redir_pipe(pipe_fd, type, current);
}
