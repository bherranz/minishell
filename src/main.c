/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/12/06 06:05:28 by codespace        ###   ########.fr       */
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
	if (cmd->ex_var)
		free(cmd->ex_var);
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
	int		i;

	ft_bzero(&mini, sizeof(t_mini));
	set_envp(&mini, envp);
	(void)argc;
	(void)argv;
	g_signal = 0;
	signals_handler();
	while (1)
	{
		mini.input = readline("MINICONCHAA > ");
		if (!mini.input)
		{
			printf("exit\n");
			if (mini.envp)
				free_array(mini.envp);
			break ;
		}
		if (mini.input)
			add_history(mini.input);
		parser(&mini);
		i = 0;
		while (i <= mini.pipes)
		{
			main_builtins(mini.cmd[i], &mini);
			i++;
		}
		if (mini.input[0] != '\0')
			free_structs(&mini);
		else
			free(mini.input);
	}
	return (0);
}
