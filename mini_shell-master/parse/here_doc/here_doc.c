/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:12:38 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:12:39 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini_shell.h"

void	heredoc(char *limitador, t_mini_shell *ms, int index)
{
	char	*buff;

	signal(SIGINT, signal_ctlc_heredoc);
	pipe(ms->cmds[index].tuvo);
	while (1)
	{
		buff = readline("here_doc>");
		if (buff == NULL || (!ft_strncmp(limitador, buff, ft_strlen(buff)) && \
		!ft_strncmp(limitador, buff, ft_strlen(limitador))))
			break ;
		write(ms->cmds[index].tuvo[1], buff, ft_strlen(buff));
		write(ms->cmds[index].tuvo[1], "\n", 1);
		free(buff);
	}
	free(buff);
	close(ms->cmds[index].tuvo[1]);
}
