/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:56 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 18:46:03 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	ms_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

static void	loop_lines(t_mini_shell *ms, char *txt, int *start)
{
	int		end;
	char	*str;
	pid_t	child;

	while (ms_strchr(txt + *start, ';') != -1)
	{
		end = ms_strchr(txt + *start, ';');
		str = gnl_substr(txt, *start, end);
		*start += end + 1;
		if (do_builtins(str, ms) == -1)
		{
			child = fork();
			if (child == 0)
				parse(str, ms);
		}
		free(str);
		waitpid(child, &ms->status, 0);
	}
}

void	find_lines(char *txt, t_mini_shell *ms)
{
	int		start;
	int		end;
	pid_t	child;

	start = 0;
	end = 0;
	if (manage_quotes(txt, ms) == 1)
		return ;
	g_id_signal = 1;
	loop_lines(ms, txt, &start);
	if (do_builtins(txt + start, ms) == -1)
	{
		child = fork();
		if (child == 0)
			parse(txt + start, ms);
		free(txt);
		waitpid(child, &(ms->status), 0);
	}
}
