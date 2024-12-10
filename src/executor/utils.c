/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:49:59 by miparis           #+#    #+#             */
/*   Updated: 2024/12/10 09:54:33 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_fds(t_io_file *fds)
{
	t_io_file	*current;

	current = fds;
	while (current)
	{
		if (current->fd != -1)
			close(current->fd);
		current = current->next;
	}
}

void	replace_dup2(t_io_file *fds, int pipe_fd, int type)
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
				exit(-1); //ver como hago pa liberar
			}
			break;
		}
		close(current->fd);
		current = current->next;
	}
	if (!current && pipe_fd >= 0)
	{
		if (dup2(pipe_fd, type) == -1)
		{
			print_error("Error: dup2", "", 0, -1);
			exit(-1); //ver como hago pa liberar
		}
	}
}
