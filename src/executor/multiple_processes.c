/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:27:55 by miparis           #+#    #+#             */
/*   Updated: 2024/11/26 10:11:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	multiple_processes(t_struct *t_struct, char **envp, int argc)
{
	pid_t	current_child;
	int		status;

	control(t_struct);
	set_cmds_num(t_struct, argc);
	first_process(t_struct, envp);
	while (t_struct->cmds_num > 1 && t_struct->cmd_index < argc - 2)
	{
		middle_process(t_struct, envp);
		t_struct->cmd_index++;
	}
	if (t_struct->cmds_num == 1)
		last_process(t_struct, envp, argc);
	while (1)
	{
		current_child = waitpid(-1, &status, 0);
		if (current_child == -1)
			break ;
		if (current_child == t_struct->last_pid)
			t_struct->status = status;
	}
	close(t_struct->old_pipe[READ]);
}

void	first_process(t_struct *t_struct, char **envp)
{
	pid_t	pid;

	pid = create_process();
	if (pid == 0)
	{
		dup2(t_struct->infile, STDIN_FILENO);
		close(t_struct->infile);
		dup2(t_struct->old_pipe[WRITE], STDOUT_FILENO);
		close(t_struct->old_pipe[WRITE]);
		close(t_struct->old_pipe[READ]);
		to_excve(t_struct, t_struct->argv, envp);
	}
	t_struct->cmd_index++;
	t_struct->cmds_num--;
	close(t_struct->infile);
	close(t_struct->old_pipe[WRITE]);
}

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
}

void	to_excve(t_struct *t_struct, char *argv[], char **envp)
{
	char	*command_path;

	t_struct->arguments = get_args(argv[t_struct->cmd_index]);
	command_path = find_path(t_struct->arguments[0], envp);
	if (execve(command_path, t_struct->arguments, envp) == -1)
	{
		perror("Execve failed 1");
		exit(127);
	}
	ft_free(t_struct->arguments);
}
