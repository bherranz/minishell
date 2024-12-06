/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_finder_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:48 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:49 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	add_infile(t_mini_shell *ms, int index, int count)
{
	ms->cmds[index].infiles = (char **)malloc(sizeof(char *) * \
	(count + 1));
	if (!ms->cmds[index].infiles)
		return ;
	ms->cmds[index].infiles[count] = NULL;
}

void	count_infiles(char *txt, t_mini_shell *ms)
{
	int	i;
	int	index;
	int	count;

	count = 0;
	i = 0;
	index = 0;
	while (txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			add_infile(ms, index, count);
			++index;
			count = 0;
		}
		else if (txt[i] == '<')
		{
			if (txt[i + 1] == '<')
				i++;
			else
				count++;
		}
		++i;
	}
	add_infile(ms, index, count);
}
