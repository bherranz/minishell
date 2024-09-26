/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/26 09:41:20 by miparis          ###   ########.fr       */
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
	tokenize(mini); //tokenizar y guardar
	//count_pipes(mini);
	//splitear aka tokenizar y guardar

}

int	count_pipes(t_mini *mini)
{
	int		p_count;
	int		quote;
	int		i;
	char	last_char;

	p_count = 0;
	i = -1;
	quote = 0;
	last_char = '\0';
	while (mini->input[++i])
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
		{
			if (quote == 0)
				quote = mini->input[i];
			else if (quote == mini->input[i])
				quote = 0;
		}
		if (mini->input[i] == '|' && quote == 0)
		{
			if (last_char == '|')
			{
				print_error("Error: syntax error near token '|'", 0, 258);
				return (-1);
			}
			p_count++;
		}
		if (mini->input[i] != ' ')
			last_char = mini->input[i];
	}
	printf("---->>> pipes found: %d\n", p_count);
	return (p_count);
}

int	tokenize(t_mini *mini)
{
	int i = 0;
	int pipes;
	
	pipes = count_pipes(mini);//contar los pipes no entrecomillados para memoria
	if (pipes < 0)
		return (-1);
	mini->cmds = malloc((pipes + 1) * sizeof(char **));
	if (!mini->cmds)
	{
		print_error("Error: Problem with memory", 0, 258);
		return (-1);
	}
	mini->cmds = ft_split(mini->input, '|'); //sirve salvo que pipe este entre comillas
	if (!mini->cmds)
	{
		print_error("Error: Problem with cmd split", 0, 258);
		return (-1);
	}
	while (mini->cmds[i])
	{
		printf("---->>> cmd[%d]: %s\n", i, mini->cmds[i]);
		i++;
	}
	return (0);
}
