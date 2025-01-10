/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:30:16 by codespace         #+#    #+#             */
/*   Updated: 2025/01/07 12:21:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_built_in(t_cmd *cmd, t_mini *mini)
{
	printf("built-in\n");
	main_builtins(cmd, mini);
}

void	single_process(t_cmd *cmd, t_mini *mini)
{
	pid_t		pid;
	t_io_file	*infile;
	t_io_file	*outfile;
	int			status; 

	infile = cmd->infile;
	outfile = cmd->outfile;
	pid = create_process();
	if (pid == 0)
	{
		if (infile)
			replace_dup2(infile, 0, STDIN_FILENO);
		if (outfile)
			replace_dup2(outfile, 0, STDOUT_FILENO);
		to_excve(cmd, mini);
	}
	close_fds(cmd->infile);
	close_fds(cmd->outfile);
	waitpid(pid, &status, 0);
	mini->last_status = WEXITSTATUS(status);
}

void	one_cmd(t_cmd *cmd, t_mini *mini)
{
	if (is_builtin(cmd->args[0]))
		exec_built_in(cmd, mini);
	else
		single_process(cmd, mini);
}
