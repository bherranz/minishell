/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2024/10/08 05:27:07 by codespace        ###   ########.fr       */
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
	if (parse_cmds(mini) == -1) //parsear comandos
		return ;
}

//voy a hacer una función de mierda, 
//luego si se nos ocurre algo mejor se cambia xd
void	count_err(char *input)
{
	if (ft_strrchr(input, '|') == NULL)
		return ;
	print_error("Error: syntax error near '|'", 0, 258);
	return ;
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
				return (print_error("Error:syntax error near '|'", 0, 258), -1);
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
	t_cmd	newcmd;

	x = 0;
	mini->pipes = count_pipes(mini);//contar los pipes no entrecomillados para memoria
	if (mini->pipes < 0)
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
