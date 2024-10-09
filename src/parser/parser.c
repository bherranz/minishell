/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2024/10/04 07:47:51 by codespace        ###   ########.fr       */
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
}

// falla en caso | echo hola | grep h | cat -> no lo toma como error
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
	if (prev == '|')
		return (print_error("Error: syntax error near token '|'", 0, 258), -1);
	return (p_count);
}

int	tokenize(t_mini *mini)
{
	int		x;
	t_cmd	newcmd;
	
	x = 0;
	mini->pipes = count_pipes(mini);
	if (mini->pipes  < 0)
		return (-1);
	mini->cmd = malloc((mini->pipes + 1) * sizeof(t_cmd));
	if (get_cmds(mini->input, '|', mini) == -1)
		return (-1);
	while (x <= mini->pipes)
	{
		mini->cmd[x] = &newcmd;
		mini->cmd[x]->full_cmd = mini->cmds[x];
		printf("--->> Guardado: %s\n", mini->cmd[x]->full_cmd);
		x++;
	}
	return (0);
}
