/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:27:55 by miparis           #+#    #+#             */
/*   Updated: 2025/01/12 23:47:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//hacer que todas las funciones devuelvan -1 en caso de 
//error para liberar los recursos en executor

void	multiple_processes(t_cmd *cmd, t_mini *mini, t_pipe *pipes)
{
	int		n_cmds;

	n_cmds = mini->pipes + 1;
	
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

void	first_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini)
{
	pid_t		pid;

	pid = create_process();
	if (pid == 0)
	{
		if (open_files(cmd, mini))
			exit(mini->last_status);
		if (cmd->infile)
			replace_dup2(cmd->infile, 0, STDIN_FILENO, mini);
		if (cmd->outfile)
			replace_dup2(cmd->outfile, 0, STDOUT_FILENO, mini);
		else if (!cmd->outfile)
			replace_dup2(NULL, pipes->old_pipe[WRITE], STDOUT_FILENO, mini);
		close(pipes->old_pipe[WRITE]);
		close(pipes->old_pipe[READ]);
        to_excve(cmd, mini);
	}
	if (cmd->infile)
		close_fds(cmd->infile);
	if (cmd->outfile)
		close_fds(cmd->outfile);
    close(pipes->old_pipe[WRITE]);
}

void	middle_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini)
{
	pid_t	pid;

	create_pipe(pipes);
	pid = create_process();
	if (pid == 0)
	{
		if (open_files(cmd, mini))
			exit(mini->last_status);
		if (cmd->infile)
			replace_dup2(cmd->infile, 0, STDIN_FILENO, mini);
		else if (!cmd->infile)
			replace_dup2(NULL, pipes->old_pipe[READ], STDIN_FILENO, mini);
		if (cmd->outfile)
			replace_dup2(cmd->outfile, 0, STDOUT_FILENO, mini);
		else if (!cmd->outfile)
			replace_dup2(NULL, pipes->new_pipe[WRITE], STDOUT_FILENO, mini);
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
    pid_t		pid;


    pid = create_process();
    if (pid == 0)
    {
		if (open_files(cmd, mini))
			exit(mini->last_status);
        if (cmd->infile)
			replace_dup2(cmd->infile, 0, STDIN_FILENO, mini);
        else if (!cmd->infile)
			replace_dup2(NULL, pipes->old_pipe[READ], STDIN_FILENO, mini);
        if (cmd->outfile)
			replace_dup2(cmd->outfile, 0, STDOUT_FILENO, mini);
        close(pipes->old_pipe[READ]);
        close(pipes->old_pipe[WRITE]);
        to_excve(cmd, mini);
    }
	close_fds(cmd->infile);
	close_fds(cmd->outfile);
    close(pipes->old_pipe[READ]);
	pipes->last_pid = pid;
}

void	to_excve(t_cmd *cmd, t_mini *mini)
{
	char	*command_path;

	if (is_builtin(cmd->args[0]))
	{
		main_builtins(cmd, mini);
		exit(mini->last_status);
	}
	command_path = find_path(cmd->args[0], mini->envp);
	if (!command_path)
	{
		print_error("Error: command not found ", "", 0, 127);
		close_fds(cmd->infile);
		close_fds(cmd->outfile);
		mini->last_status = 127;
		exit(mini->last_status);
	}
	if (execve(command_path, cmd->args, mini->envp) == -1)
	{
		print_error("Error: command not found ", "", 0, 127);
		close_fds(cmd->infile);
		close_fds(cmd->outfile);
		mini->last_status = 127;
		exit(mini->last_status);
	}
	ft_free(cmd->args);
}
