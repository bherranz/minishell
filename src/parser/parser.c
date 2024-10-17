/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2024/10/17 12:02:00 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes(t_mini *mini)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
		{
			if (quote == 0)
				quote = mini->input[i];
			//asegurar que la comilla de cierre es la misma que la de apertura
			else if (quote == mini->input[i])
				quote = 0;
		}
		i++;
	}
	if (quote)
	{
		print_error("Error: unclosed quotes", 0, 258);
		return (1);
	}
	return (0);
}

void	parser(t_mini *mini)
{
	if (check_quotes(mini)) //check comillas cerradas
		return ;
	if (tokenize(mini) == -1) //tokenizar y guardar
		return ;
	int i = -1;
	while (mini->cmd[++i])
		get_var(mini, mini->cmd[i]);
	int x = 0;
	while (x <= mini->pipes)
	{
		printf("--->> Guardado: %s\n", mini->cmd[x]->full_cmd);
		x++;
	}
}

int	count_pipes(t_mini *mini)
{
	int		p_count;
	int		quote;
	int		i;
	char	prev;

	p_count = 0;
	i = -1;
	quote = 0;
	prev = '|';
	while (mini->input[++i])
	{
		is_quote(mini->input[i], &quote);
		if (mini->input[i] == '|' && quote == 0)
		{
			if (prev == '|')
				return (print_error("Error:syntax error near token '|'", 0, 258), -1);
			p_count++;
		}
		if (mini->input[i] != ' ')
			prev = mini->input[i];
	}
	if (prev == '|') //si solo hay espacios tira error, creo que es mejor devolver control a usuario y ya
		return (count_err(mini->input), -1);
	return (p_count);
}

int	tokenize(t_mini *mini)
{
	int		x;

	x = 0;
	mini->pipes = count_pipes(mini);//contar los pipes no entrecomillados para memoria
	if (mini->pipes < 0)
		return (-1);
	mini->cmd = (t_cmd **)malloc((mini->pipes + 1) * sizeof(t_cmd *));
	if (!mini->cmd)
	{
		print_error("Error: Problem with allocating commands structs", 0, 258);
		return (-1);
	}
	if (get_cmds(mini->input, '|', mini) == -1) //sirve salvo que pipe este entre comillas	
		return (-1);
	while (x <= mini->pipes)
	{
		mini->cmd[x] = init_tcmd();
		if (!mini->cmd[x])
		{
			print_error("Error: Command string null", 0, 258);
			return (-1);
		}
		mini->cmd[x]->full_cmd = mini->cmds[x];
		mini->cmd[x]->index = x;
		x++;
	}
	return (0);
}

t_cmd *init_tcmd()
{
	t_cmd *cmd;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->index = 0;
	cmd->full_cmd = NULL;
	cmd->simple = 0;
	cmd->doble = 0;
	cmd->key = 0;
	cmd->e_input = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	return (cmd);
}
