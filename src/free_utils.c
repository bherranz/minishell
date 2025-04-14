/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:12:06 by codespace         #+#    #+#             */
/*   Updated: 2025/02/09 23:45:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_io_files(t_io_file *file_list)
{
	t_io_file	*temp;

	while (file_list)
	{
		temp = file_list;
		if (temp->fd > -1)
			close(temp->fd);
		file_list = file_list->next;
		free(temp->name);
		free(temp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile)
		free_io_files(cmd->infile);
	if (cmd->outfile)
		free_io_files(cmd->outfile);
	if (cmd->e_input)
		free(cmd->e_input);
	if (cmd->full_cmd)
		free(cmd->full_cmd);
	if (cmd->args)
		free_array(cmd->args);
	if (cmd)
		free(cmd);
}

void	free_structs(t_mini *mini)
{
	int	i;

	if (mini->cmds)
		free_array(mini->cmds);
	i = 0;
	if (mini->cmd)
	{
		while (i <= mini->pipes_n)
		{
			if (mini->cmd[i])
				free_cmd(mini->cmd[i]);
			i++;
		}
		free(mini->cmd);
	}
	if (mini->input)
		free(mini->input);
	if (mini->pipes)
		free(mini->pipes);
}
