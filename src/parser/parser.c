/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2025/01/19 11:44:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parser(t_mini *mini)
{
	int	i;

	i = 0;
	if (check_quotes(mini))
		return (1);
	if (tokenize(mini) == -1)
		return (1);
	while (i <= mini->pipes_n)
	{
		if (expand(mini, mini->cmd[i]) == -1)
			return (1);
		i++;
	}
	if (parse_cmds(mini) == -1)
		return (1);
	return (0);
}

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
			else if (quote == mini->input[i])
				quote = 0;
		}
		i++;
	}
	if (quote)
	{
		print_error("Error: unclosed quotes", "", 0, 258);
		return (1);
	}
	return (0);
}

int	count_err(char *input)
{
	if (ft_strrchr(input, '|') == NULL)
		return (0);
	print_error("Error: syntax error near '|'", "", 0, 258);
	return (-1);
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
				return (count_err(mini->input));
			p_count++;
		}
		if (mini->input[i] != ' ')
			prev = mini->input[i];
	}
	if (prev == '|')
		return (count_err(mini->input));
	return (p_count);
}

int	tokenize(t_mini *mini)
{
	int		x;

	x = 0;
	mini->pipes_n = count_pipes(mini);
	if (mini->pipes_n < 0)
		return (-1);
	mini->cmd = (t_cmd **)malloc((mini->pipes_n + 1) * sizeof(t_cmd *));
	if (!mini->cmd)
		return (print_error("Error: Fail allocating structs", "", 0, 258), -1);
	if (get_cmds(mini->input, '|', mini) == -1)
		return (-1);
	while (x <= mini->pipes_n)
	{
		mini->cmd[x] = init_tcmd();
		if (!mini->cmd[x])
			return (print_error("Error: Command string null", "", 0, 258), -1);
		mini->cmd[x]->full_cmd = ft_strdup(mini->cmds[x]);
		mini->cmd[x]->index = x;
		x++;
	}
	return (0);
}
