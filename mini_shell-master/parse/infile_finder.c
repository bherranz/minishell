/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:51 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 14:50:38 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static char	*get_infile(char *txt, int start, t_mini_shell *ms)
{
	int		i;
	int		end;
	char	*infile;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && txt[i + end] != ' ' && txt[i + end] != '|' \
	&& txt[i + end] != '<' && txt[i + end] != '>')
	{
		if (txt[i + end] == '\'' || txt[i + end] == '\"')
			end += skip_quotes(txt + i + end, txt[i + end]);
		end++;
	}
	if (end > 0)
		infile = ft_substr(txt, i, end);
	else
	{
		printf("🐦‍🔥minishell> Error: syntax error\n");
		exit (1);
	}
	return (clean_quotes(infile, ms));
}

static char	*get_limit(char *txt, int start, t_mini_shell *ms)
{
	int	i;
	int	end;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9)))
		i++;
	if (txt[i] == '\'' || txt[i] == '\"')
		return (get_literal(txt, &i));
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		return (clean_quotes(ft_substr(txt, i, end), ms));
	else
		return (clean_quotes(ft_substr(txt, 0, 0), ms));
}

static void	loop_infile(char *txt, int *indexes, t_mini_shell *ms, char *lim)
{
	if (txt[indexes[I]] == '|' || txt[indexes[I]] == ';')
	{
		indexes[FILE_INDEX] = 0;
		indexes[INDEX]++;
		ms->cmds[indexes[INDEX]].here_doc = 0;
	}
	else if (txt[indexes[I]] == '\'' || txt[indexes[I]] == '\"')
		indexes[I] += skip_quotes(txt + indexes[I], txt[indexes[I]]);
	if (txt[indexes[I]] == '<')
	{
		if (txt[indexes[I] + 1] == '<')
		{
			indexes[I]++;
			lim = get_limit(txt, indexes[I], ms);
			heredoc(lim, ms, indexes[INDEX]);
			free(lim);
			ms->cmds[indexes[INDEX]].here_doc = 1;
		}
		else
		{
			ms->cmds[indexes[INDEX]].infiles[indexes[FILE_INDEX]] \
			= get_infile(txt, indexes[I], ms);
			ms->cmds[indexes[INDEX]].here_doc = 0;
			indexes[FILE_INDEX]++;
		}
	}
}

void	find_infile(char *txt, t_mini_shell *ms)
{
	char	*limitador;
	int		indexes[3];

	indexes[I] = 0;
	indexes[INDEX] = 0;
	indexes[FILE_INDEX] = 0;
	ms->cmds[indexes[INDEX]].here_doc = 0;
	ms->cmds[0].infiles = NULL;
	limitador = NULL;
	count_infiles(txt, ms);
	while (txt[indexes[I]])
	{
		loop_infile(txt, indexes, ms, limitador);
		indexes[I]++;
	}
}
