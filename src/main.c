/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/11/27 10:50:11 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal; //variable global

void	free_io_files(t_io_file *file_list)
{
	t_io_file	*temp;

	while (file_list)
	{
		temp = file_list;
		file_list = file_list->next;
		free(temp->name);
		free(temp);
	}
}

void free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile)
		free_io_files(cmd->infile);
	if (cmd->outfile)
		free_io_files(cmd->outfile);
	/*if (cmd->full_cmd)
		free(cmd->full_cmd);*/
	if (cmd->e_input)
		free(cmd->e_input);
	if (cmd->ex_var)
		free(cmd->ex_var);
	if (cmd->args)
		free_array(cmd->args);
	if (cmd)
		free(cmd);
}

void free_structs(t_mini *mini)
{
	int	i;

	if (mini->cmds)
		free_array(mini->cmds);
	i = 0;
	if (mini->cmd)
	{
		while (i <= mini->pipes)
		{
			if (mini->cmd[i])
				free_cmd(mini->cmd[i]);
			i++;		
		}
		free(mini->cmd);
	}
	free(mini->input);
}


int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	ft_bzero(&mini, sizeof(t_mini));
	mini.envp = envp;
	(void)argc;
	(void)argv;
	g_signal = 0;
	signals_handler();
	while (1)
	{
		mini.input = readline("MINICONCHAA > ");
		if (!mini.input || ft_strcmp(mini.input, "exit") == 0)
		{
			printf("exit\n");
			if (mini.input)
				free(mini.input);
			break ;
		}
		if (mini.input)
			add_history(mini.input);
		parser(&mini);
		executor(&mini);
		free(mini.input);
	}
	free_structs(&mini);
	return (0);
}
