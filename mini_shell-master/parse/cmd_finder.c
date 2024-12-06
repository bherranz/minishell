/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:46 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:47 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	get_cmd(char *txt, t_mini_shell *ms, int index, int *i)
{
	int		end;
	char	*aux;

	end = 0;
	while (txt[*i + end] && txt[*i + end] != '|' && (txt[*i + end] != ' ' || \
	txt[*i + end] == '-') && ft_valid_name_char(txt[*i + end]))
	{
		if (txt[*i + end] == '\'' || txt[*i + end] == '\"')
			end += skip_quotes(txt + *i + end, txt[*i + end]);
		++end;
	}
	if (ms->cmds[index].cmd != NULL)
		ms->cmds[index].cmd = gnl_strjoin(ms->cmds[index].cmd, " ");
	aux = gnl_substr(txt, *i, end);
	if (!ms->cmds[index].awk)
		ms->cmds[index].cmd = clean_quotes(\
		gnl_strjoin(ms->cmds[index].cmd, aux), ms);
	else
		ms->cmds[index].cmd = gnl_strjoin(ms->cmds[index].cmd, aux);
	free(aux);
	if (!ft_strncmp(ms->cmds[index].cmd, "awk", 3))
		ms->cmds[index].awk = 1;
	*i += end;
}

void	skip_word(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] != ' ' && !(txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

void	skip_file(char *txt, int *i)
{
	*i += 1;
	if (txt[*i] && ft_valid_name_char(txt[*i]))
	{
		while (ft_valid_name_char(txt[*i]) && txt[*i] != '|')
			*i += 1;
		return ;
	}
	else if (txt[*i] && (txt[*i] == ' ' || (txt[*i] <= 13 && txt[*i] >= 9)))
	{
		skip_spaces(txt, i);
		while (ft_valid_name_char(txt[*i]))
			*i += 1;
	}
}

static void	cmd_loop(char *txt, int index, t_mini_shell *ms)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			index++;
			i++;
		}
		else if (txt[i] == '<' || txt[i] == '>')
			skip_file(txt, &i);
		else if (ft_valid_name_char(txt[i]) || \
		txt[i] == '-' || txt[i] == '\'' || txt[i] == '\"')
			get_cmd(txt, ms, index, &i);
		else if (txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9))
			skip_spaces(txt, &i);
		else
		{
			skip_word(txt, &i);
			txt++;
		}
	}
}

void	find_cmd(char *txt, t_mini_shell *ms)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (i < ms->num_cmds)
	{
		ms->cmds[i].awk = 0;
		ms->cmds[i].cmd = NULL;
		i++;
	}
	cmd_loop(txt, index, ms);
}
