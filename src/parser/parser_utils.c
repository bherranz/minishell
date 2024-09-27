/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:10:27 by miparis           #+#    #+#             */
/*   Updated: 2024/09/27 10:10:28 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	ft_free(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free (array);
}

static char	**ft_fill(const char *s, char c, char **array, size_t substrings)
{
	size_t	i;
	size_t	j;
	int		quote;

	i = -1;
	j = 0;
	quote = 0;
	while (++i < substrings)
	{
		while (s[j] && s[j] == c && !quote)
			j++;
		array[i] = ft_substr(s, j, ft_customstrlen((s + j), c));
		if (!array[i])
			return (ft_free(i, array), NULL);
		while (s[j] && (s[j] != c || quote))
		{
			is_quote(s[j], &quote);
			j++;
		}
	}
	return (array[i] = NULL , array);
}

int	get_cmds(char const *s, char c, t_mini *mini)
{
	if (!s)
		return (-1);
	mini->cmds = (char **)malloc(sizeof(char *) * (mini->pipes + 1));
	mini->cmds = ft_fill(s, c, mini->cmds, (mini->pipes + 1));
	if (!mini->cmds)
	{
		print_error("Error: Problem with getting commands", 0, 258);
		return (-1);
	}
	return (0);
}

