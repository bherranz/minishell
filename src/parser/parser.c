/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 02:17:39 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/24 05:49:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_quotes(t_mini *mini)
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
		print_error("Error: unclosed quotes", 0, 258);
}

void	parser(t_mini *mini)
{
	check_quotes(mini);
}
