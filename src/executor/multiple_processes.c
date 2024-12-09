/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:27:55 by miparis           #+#    #+#             */
/*   Updated: 2024/12/09 11:51:45 by miparis          ###   ########.fr       */
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
	if (n_cmds == 1)
	{
		printf("---> SIngle process...\n");
		single_process(cmd, mini);
	}
	if (n_cmds > 1 && cmd->index == 0)
	{
		printf("---> First process...\n");
		first_process(cmd, pipes, mini);
	}
	if (cmd->index > 0 && cmd->index < n_cmds - 1)
	{
		printf("---> Midle process...\n");
		middle_process(cmd, pipes, mini);
	}
	if (n_cmds > 1 && cmd->index == n_cmds - 1)
	{
		printf("---> Last process...\n");
		last_process(cmd, pipes, mini);
	}
}
void	single_process(t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	t_io_file 	*infile;
	t_io_file 	*outfile;

	infile = cmd->infile;
	outfile = cmd->outfile;
	pid = create_process();
	if (pid == 0)
	{
		if (infile)
			replace_dup2(infile, STDIN_FILENO);
		if (outfile)
			replace_dup2(outfile, STDOUT_FILENO);
        to_excve(cmd, mini);
	}
	close_fds(cmd->infile);
	close_fds(cmd->outfile);
	waitpid(pid, NULL, 0);
	mini->last_status = WEXITSTATUS(pid);
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
					break ;
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
		else if (!outfile)
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
        to_excve(cmd, mini);
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

void	middle_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini)
{
	pid_t	pid;
	t_io_file 	*infile;
	t_io_file 	*outfile;

	infile = cmd->infile;
	outfile = cmd->outfile;
	if (pipe(pipes->new_pipe) < 0)
	{
		printf("Problem with pipe\n");
		exit (1);
	}
	pid = create_process();
	if (pid == 0)
	{
		if (infile)
		{
			while (infile)
			{
				if(infile->last_in)
				{
					dup2(infile->fd, STDIN_FILENO);
					break ;
				}
				close(infile->fd);
				infile = infile->next;
			}
		}
		else
		{
			//ver si hace falta control de error en dup2
			if (dup2(pipes->old_pipe[READ], STDIN_FILENO) == -1)
			{
                perror("dup2 pipe");
                exit(1);
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
		else
		{
			//ver si hace falta control de error en dup2
			if (dup2(pipes->new_pipe[WRITE], STDOUT_FILENO) == -1)
			{
                perror("dup2 pipe");
                exit(1);
            }
		}
		close(pipes->old_pipe[READ]);
		close(pipes->new_pipe[READ]);
		close(pipes->new_pipe[WRITE]);
        to_excve(cmd, mini);
	}
	close(pipes->old_pipe[READ]);
	pipes->old_pipe[READ] = pipes->new_pipe[READ];
	close(pipes->new_pipe[WRITE]);
}

void	last_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini)
{
    pid_t pid;
    t_io_file *infile = cmd->infile;
    t_io_file *outfile = cmd->outfile;

    pid = create_process();
    if (pid == 0)
    {
        // Redirigir STDIN
        if (infile)
        {
            while (infile)
            {
                if (infile->last_in)
                {
                    if (dup2(infile->fd, STDIN_FILENO) == -1)
                    {
                        perror("dup2 infile");
                        exit(1);
                    }
                    break;
                }
                close(infile->fd);
                infile = infile->next;
            }
        }
        else
        {
            if (dup2(pipes->old_pipe[READ], STDIN_FILENO) == -1)
            {
                perror("dup2 old_pipe[READ]");
                exit(1);
            }
        }

        // Redirigir STDOUT
        if (outfile)
        {
            while (outfile)
            {
                if (outfile->last_in)
                {
                    if (dup2(outfile->fd, STDOUT_FILENO) == -1)
                    {
                        perror("dup2 outfile");
                        exit(1);
                    }
                    break;
                }
                close(outfile->fd);
                outfile = outfile->next;
            }
        }
        // Cerrar descriptores no necesarios
        close(pipes->old_pipe[READ]);
        close(pipes->old_pipe[WRITE]);
        to_excve(cmd, mini);
    }
    // En el proceso padre, cerrar descriptores de infile y outfile
    if (cmd->infile)
    {
        while (cmd->infile)
        {
            close(cmd->infile->fd);
            cmd->infile = cmd->infile->next;
        }
    }
    if (cmd->outfile)
    {
        while (cmd->outfile)
        {
            close(cmd->outfile->fd);
            cmd->outfile = cmd->outfile->next;
        }
    }
    close(pipes->old_pipe[READ]);
	pipes->last_pid = pid;
}

void	to_excve(t_cmd *cmd, t_mini *mini)
{
	char	*command_path;

	command_path = find_path(cmd->args[0], mini->envp);
	if (!command_path)
	{
		print_error("Error: command not found ", "", 0, 127);
		close_fds(cmd->infile);
		close_fds(cmd->outfile);
		exit(127);
	}
	free(cmd->args[0]);
	cmd->args[0] = command_path;
	/*if (is_builtin(cmd->args[0]))
		builtin(cmd->args[0])*/
	if (execve(cmd->args[0], cmd->args, mini->envp) == -1)
	{
		print_error("Error: command not found ", "", 0, 127);
		close_fds(cmd->infile);
		close_fds(cmd->outfile);
		exit(127);
	}
	ft_free(cmd->args);
}
