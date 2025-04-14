/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:30:16 by codespace         #+#    #+#             */
/*   Updated: 2025/01/18 16:09:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_built_in(t_cmd *cmd, t_mini *mini)
{
	if (open_files(cmd, mini))
		return ;
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	if (cmd->infile)
		replace_dup2(cmd->infile, 0, STDIN_FILENO, mini);
	if (cmd->outfile)
		replace_dup2(cmd->outfile, 0, STDOUT_FILENO, mini);
	main_builtins(cmd, mini);
	if (dup2(mini->stdin, STDIN_FILENO) == -1
		|| dup2(mini->stdout, STDOUT_FILENO) == -1)
	{
		print_error("Error: dup2", "", 0, -1);
		mini->last_status = 1;
	}
	close(mini->stdin);
	close(mini->stdout);
	close_fds(cmd->infile);
	close_fds(cmd->outfile);
}

void	single_process(t_cmd *cmd, t_mini *mini)
{
	pid_t		pid;
	int			status;

	pid = create_process();
	if (pid == 0)
	{
		try_open(cmd, mini);
		if (cmd->infile)
			replace_dup2(cmd->infile, 0, STDIN_FILENO, mini);
		if (cmd->outfile)
			replace_dup2(cmd->outfile, 0, STDOUT_FILENO, mini);
		close_pipe_struct(mini->pipes);
		to_excve(cmd, mini);
	}
	close_fds(cmd->infile);
	close_fds(cmd->outfile);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		mini->last_status = 128 + WTERMSIG(status);
}

void	one_cmd(t_cmd *cmd, t_mini *mini)
{
	if (is_builtin(cmd->args[0]))
		exec_built_in(cmd, mini);
	else
		single_process(cmd, mini);
}
