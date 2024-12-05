/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:47:28 by miparis           #+#    #+#             */
/*   Updated: 2024/11/29 17:29:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	executor(t_mini *mini)
{
	t_pipe		*pipes;
	pid_t		current_child;
	int			i;
	int			status;

	pipes = malloc(sizeof(*pipes));
	set_struct(pipes);
	if (control(pipes))
			return (-1);
	i = 0;
	while (i < (mini->pipes + 1) && mini->cmd[i])
	{
		if (open_files(mini->cmd[i]))
			return (-1);
		//case_setter -> modificar setter dependiendo el indice del comando
		multiple_processes(mini->cmd[i], mini, pipes);
		i++;
	}
	while (1)
	{
		current_child = waitpid(-1, &status, 0);
		if (current_child == -1)
			break ; //aqui agreagar liberacion de memoria
		if (current_child == pipes->last_pid)
			pipes->status = status;
	}
	close(pipes->old_pipe[READ]);
	free(pipes);
	return (0);
}

int	open_files(t_cmd *cmd)
{
	if (cmd->infile)
	{
		print_list(cmd->infile);
		if (infiles(cmd->infile))
			return (-1);
	}
	if (cmd->outfile)
	{
		print_list(cmd->outfile);
		if (outfiles(cmd->outfile))
			return (-1);		
	}
	return (0);
}

int 	fd_control(t_io_file *current)
{
	if (current->fd == -1)
	{
		print_error("Error: no such file or directory: ", current->name, 0, 258);
		return (1);
	}
	return (0);
}
int 	outfiles(t_io_file *outfiles)
{
	t_io_file 	*current;
	
	current = outfiles;
	while (current)
	{
		if (current->type == 3) // >
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_control(current))
				return (-1);	
		}
		if (current->type == 4) // >> 
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_control(current))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

int 	infiles(t_io_file *infiles)
{
	t_io_file 	*current;
	
	current = infiles;
	while (current)
	{
		if (current->type == 2) // <<
		{
			if (process_here_doc(current))
				return (-1);
			if (fd_control(current))
				return (-1);
			unlink("/tmp/temp_file"); //-> agregado por si quitan ppermisos
		}
		else
		{
			current->fd = open(current->name, O_RDONLY); // <
			if (fd_control(current))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}
