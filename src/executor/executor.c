/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:47:28 by miparis           #+#    #+#             */
/*   Updated: 2024/12/09 11:54:23 by miparis          ###   ########.fr       */
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
	//ver no se esta guardando bien el codigo de retorno del ultimo proceso
	while (1)
	{
		current_child = waitpid(-1, &status, 0);
		if (current_child == -1)
		{
			break ; //aqui agreagar liberacion de memoria
		}
		if (current_child == pipes->last_pid)
		{
			pipes->status = status;
			//mini->last_status = status;
		}
	}
	close(pipes->old_pipe[READ]);
	free(pipes);
	return (0);
}
