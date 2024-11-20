/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:10:27 by miparis           #+#    #+#             */
/*   Updated: 2024/11/20 11:20:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*init_tcmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd)); //leak
	cmd->index = 0;
	cmd->full_cmd = NULL;
	cmd->simple = 0;
	cmd->doble = 0;
	cmd->e_input = NULL;
	cmd->ex_var = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->args_index = 0;
	return (cmd);
}

int	is_quote(char c,  int *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
	return (*quote);
}

static size_t	ft_customstrlen(const char *s, char c)
{
	size_t	i;
	int	quote;

	i = 0;
	quote = 0;
	while (s[i] != '\0' && (s[i] != c || quote))
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (quote == 0)
				quote = s[i];
			else if (quote == s[i])
				quote = 0;
		}
		i++;
	}
	return (i);
}

static char	**ft_fill(const char *s, char c, char **array, size_t substrings)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	while (i < substrings)
	{
		while (s[j] && s[j] == c && !quote)
			j++;
		array[i] = ft_substr(s, j, ft_customstrlen((s + j), c));// leak
		if (!array[i])
			return (ft_free(array), NULL);
		while (s[j] && (s[j] != c || quote))
		{
			is_quote(s[j], &quote);
			j++;
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	get_cmds(char const *s, char c, t_mini *mini)
{
	if (!s)
		return (-1);
	mini->cmds = NULL;
	mini->cmds = (char **)malloc(sizeof(char *) * (mini->pipes + 2)); // leaks
	mini->cmds = ft_fill(s, c, mini->cmds, (mini->pipes + 1)); //leak
	if (!mini->cmds)
	{
		print_error("Error: Problem with getting commands", "", 0, 258);
		return (-1);
	}
	return (0);
}
