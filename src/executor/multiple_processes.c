/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:27:55 by miparis           #+#    #+#             */
/*   Updated: 2024/11/28 11:18:54 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	multiple_processes(t_cmd *cmd, t_mini *mini, t_pipe *pipes)
{
	int		n_cmds;

	n_cmds = mini->pipes + 1;
	printf("->> Cmd Index == %d\n", cmd->index);
	/*if (cmd->index == 0 && (is_builtin(mini->cmd[i]->args[0]) == 1))
			//execute built_in in father*/
	if (cmd->index == 0)
	{
		printf("---> First process...\n");
		first_process(cmd, pipes, mini);
	}
	if (cmd->index > 0 && cmd->index < n_cmds - 1)
	{
		printf("---> Midle process...\n");
		//middle_process(cmd, mini, pipe);
	}
	if (cmd->index == n_cmds - 1)
	{
		printf("---> Last process...\n");
		//last_process(cmd, mini, pipe);
	}
}

void	first_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini)
{
	pid_t		pid;
	t_io_file 	*infile;
	t_io_file 	*outfile;

	infile = cmd->infile;
	outfile = cmd->outfile;
	pid = create_process();
	if (pid == 0)
	{
		//hacer dup2 del ULTIMO infile en la lista
		if (infile)
		{
			while (infile)
			{
				if(infile->last_in)
				{
					dup2(infile->fd, STDIN_FILENO);
					break;
				}
				close(infile->fd);
				infile = infile->next;
			}
		}
		if (outfile)
		{
			while (outfile)
			{
				if(outfile->last_in)
				{
					dup2(outfile->fd, STDOUT_FILENO);
					break;
				}
				close(outfile->fd);
				outfile = outfile->next;
			}
		}
		if (!cmd->outfile)
		{
			//ver si hace falta control de error en dup2
			if (dup2(pipes->old_pipe[WRITE], STDOUT_FILENO) == -1)
			{
                perror("dup2 pipe");
                exit(1);
            }
		}
		close(pipes->old_pipe[WRITE]);
		close(pipes->old_pipe[READ]);
		to_excve(cmd, mini->envp);
	}
	if (cmd->infile)
	{ // Cerrar infiles en el proceso padre
        while (cmd->infile)
		{
            close(cmd->infile->fd);
            cmd->infile = cmd->infile->next;
        }
    }
    close(pipes->old_pipe[WRITE]);
}
/*
void	middle_process(t_struct *t_struct, char **envp)
{
	pid_t	pid;

	if (pipe(t_struct->new_pipe) < 0)
	{
		printf("Problem with pipe\n");
		exit (1);
	}
	pid = create_process();
	if (pid == 0)
	{
		dup2(t_struct->old_pipe[READ], STDIN_FILENO);
		close(t_struct->old_pipe[READ]);
		dup2(t_struct->new_pipe[WRITE], STDOUT_FILENO);
		close(t_struct->new_pipe[READ]);
		close(t_struct->new_pipe[WRITE]);
		to_excve(t_struct, t_struct->argv, envp);
	}
	close(t_struct->old_pipe[READ]);
	t_struct->old_pipe[READ] = t_struct->new_pipe[READ];
	close(t_struct->new_pipe[WRITE]);
	t_struct->cmds_num--;
}

void	last_process(t_struct *t_struct, char **envp, int argc)
{
	pid_t		pid;
	char		*temp_file;

	temp_file = t_struct->argv[argc - 1];
	t_struct->outfile = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (t_struct->outfile == -1)
	{
		printf("Problem with outfile\n");
		exit (1);
	}
	pid = create_process();
	if (pid == 0)
	{
		dup2(t_struct->old_pipe[READ], STDIN_FILENO);
		close(t_struct->old_pipe[READ]);
		close(t_struct->old_pipe[WRITE]);
		dup2(t_struct->outfile, STDOUT_FILENO);
		close(t_struct->outfile);
		to_excve(t_struct, t_struct->argv, envp);
	}
	t_struct->cmds_num--;
	t_struct->last_pid = pid;
	close(t_struct->outfile);
}*/

void	to_excve(t_cmd *cmd, char **envp)
{
	char	*command_path;

	command_path = find_path(cmd->args[0], envp);
	free(cmd->args[0]);
	cmd->args[0] = command_path;
	/*if (is_builtin(cmd->args[0]))
		builtin(cmd->args[0])*/
	if (execve(cmd->args[0], cmd->args, envp) == -1)
	{
		perror("Execve failed 1");
		exit(127);
	}
	ft_free(cmd->args);
}
