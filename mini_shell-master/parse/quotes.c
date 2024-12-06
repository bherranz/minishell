/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:09 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 11:07:33 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	count_quotes(char *txt, int *i, t_mini_shell *ms)
{
	if (txt[*i] == '\'')
	{
		(*i)++;
		while (txt[*i] && txt[*i] != '\'')
			(*i)++;
		if (!txt[*i])
		{
			printf("🐦‍🔥minishell> Error: incomplete quotes\n");
			return (1);
		}
		ms->quote = 1;
	}
	else if (txt[*i] == '\"')
	{
		(*i)++;
		while (txt[*i] && txt[*i] != '\"')
			(*i)++;
		if (!txt[*i])
		{
			printf("🐦‍🔥minishell> Error: incomplete quotes\n");
			return (1);
		}
		ms->quote = 1;
	}
	return (0);
}

int	manage_quotes(char *txt, t_mini_shell *ms)
{
	int	i;

	ms->quote = 0;
	i = 0;
	while (txt[i])
	{
		if (count_quotes(txt, &i, ms))
		{
			free(txt);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	fill_new_text(char *txt, char **new_txt, int *i, int *j)
{
	if (txt[*i] == '\'')
	{
		(*i)++;
		while (txt[*i] && txt[*i] != '\'')
		{
			(*new_txt)[*j] = txt[*i];
			(*i)++;
			(*j)++;
		}
	}
	else if (txt[*i] == '\"')
	{
		(*i)++;
		while (txt[*i] && txt[*i] != '\"')
		{
			(*new_txt)[*j] = txt[*i];
			(*i)++;
			(*j)++;
		}
	}
	else
	{
		(*new_txt)[*j] = txt[*i];
		(*j)++;
	}
}

static char	*quote_alloc(char *txt, int count)
{
	int		i;
	int		j;
	char	*new_txt;

	i = 0;
	j = 0;
	new_txt = malloc(sizeof(char) * (ft_strlen(txt) - count + 1));
	if (!new_txt)
		return (NULL);
	while (txt[i])
	{
		fill_new_text(txt, &new_txt, &i, &j);
		i++;
	}
	new_txt[j] = '\0';
	free (txt);
	return (new_txt);
}

char	*clean_quotes(char *txt, t_mini_shell *ms)
{
	int	i;
	int	count;

	if (!ms->quote)
		return (txt);
	i = 0;
	count = 0;
	while (txt[i])
	{
		if (txt[i] != '\'')
		{
			while (txt[i] && txt[i] != '\'')
				i++;
			count += 2;
		}
		else if (txt[i] != '\"')
		{
			while (txt[i] && txt[i] != '\"')
				i++;
			count += 2;
		}
		i++;
	}
	return (quote_alloc(txt, count));
}
