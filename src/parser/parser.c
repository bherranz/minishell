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
	if (tokenize(mini) == -1) //tokenizar y guardar
		return ;
}

// falla en caso | echo hola | grep h | cat -> no lo toma como error
int	count_pipes(t_mini *mini)
{
	int		p_count;
	int		quote;
	int		i;
	char	last_char;

	p_count = 0;
	i = -1;
	quote = 0;
	last_char = '|';
	while (mini->input[++i])
	{
		is_quote(mini->input[i], &quote);
		if (mini->input[i] == '|' && quote == 0)
		{
			if (last_char == '|' || mini->input[i + 1] == '\0')
			{
				print_error("Error: syntax error near token '|'", 0, 258);
				return (-1);
			}
			p_count++;
		}
		if (mini->input[i] != ' ')
			last_char = mini->input[i];
	}
	return (p_count);
}

int	tokenize(t_mini *mini)
{
	int		x;
	t_cmd	newcmd;
	
	x = 0;
	mini->pipes = count_pipes(mini);//contar los pipes no entrecomillados para memoria
	if (mini->pipes  < 0)
		return (-1);
	mini->cmd = malloc((mini->pipes + 1) * sizeof(t_cmd));
	if (get_cmds(mini->input, '|', mini) == -1) //sirve salvo que pipe este entre comillas	
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
/*
int	pipe_count(t_mini *mini)
{
	int	i;
	int	count;
	int quote;

	i = 0;
	count = 0;
	quote = 0;
	while (mini->input[i])
	{
		//clasificar si estamos dentro de comillas
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
		{
			if (quote == 0)
				quote = mini->input[i];
			else if (quote == mini->input[i])
				quote = 0;	
		}
		if (quote == 0 && mini->input[i] == '|')
			count++;
		i++;
	}
	printf("------------> Pipes nbr: %d \n", count);
	return (count);
}

void	tokenize(t_mini *mini)
{
	int	i; //iterador posición input
	int	j; //iterador número de comando
	int	length;
	int	quote;

	i = 0;
	j = 0;
	length = 0;
	quote = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
		{
			if (quote == 0)
				quote = mini->input[i];
			else if (quote == mini->input[i])
				quote = 0;	
		}
		else if (quote == 0 && mini->input[i] == '|')
		{
			length = 0;
			t_cmd newcmd;
			mini->cmd[j] = &newcmd;
			mini->cmd[j]->full_cmd = ft_substr(&mini->input[i - length], 0, length);
			j++;
		}
		length++;
		i++;
	}
	//print comands
	int x = 0;
	while (mini->cmd[x]->full_cmd)
	{
		printf("---->>> cmd[%d]: %s\n", x, mini->cmd[x]->full_cmd);
		x++;
	}
}

void	parser(t_mini *mini)
{
	if (check_quotes(mini)) //check comillas cerradas
		return ;
	//splitear aka tokenizar y guardar
	//sumar 1 porque siempre hay un comando más que pipes
	mini->cmd = malloc((pipe_count(mini) + 1) * sizeof(t_cmd));
	tokenize(mini);
}*/