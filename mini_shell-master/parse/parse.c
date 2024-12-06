/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:01 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 15:27:59 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_valid_name_char(int c)//esto dentro del awk
{
	if ((c != '<' && c != '>' && \
	c != '(' && c != ')' && c != '&' && c <= 126 && c >= 33) || \
	c == -61 || c == -111 || c == -79)
		return (1);
	else
		return (0);
}

static void	fill_struct(char *txt, t_mini_shell *ms)
{
	char	*newtxt;
	int		i;

	newtxt = expand_variables(txt, ms);
	find_infile(newtxt, ms);
	find_outfile(newtxt, ms);
	find_cmd(newtxt, ms);
	i = 0;
	while (i < ms->num_cmds)
	{
		if (!ms->cmds[i].cmd)
		{
			printf("🐦‍🔥minishell> Error: bad use of pipe\n");
			exit (1);
		}
		i++;
	}
}

static void	cmd_count(char *str, t_mini_shell *ms)
{
	ms->num_cmds = 1;
	if (!str)
		return (perror("Error"));
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str += skip_quotes(str, *str);
		if (*str == '|' || *str == ';')
			ms->num_cmds++;
		str++;
	}
}

void	parse(char *txt, t_mini_shell *ms)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 1;
	while (txt[i])
	{
		if (txt[i] != ' ')
		{
			spaces = 0;
			break ;
		}
		i++;
	}
	if (spaces)
		exit (1);
	cmd_count(txt, ms);
	ms->cmds = malloc (sizeof(t_cmds) * ms->num_cmds);
	if (!ms->cmds)
		return ;
	fill_struct(txt, ms);
	pipex(ms);
	exit (ms->status);
}
