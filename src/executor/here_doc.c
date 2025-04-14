/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:26:57 by codespace         #+#    #+#             */
/*   Updated: 2025/01/18 16:55:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_here_doc_child(int temp_file, char *delimiter, t_mini *mini)
{
	char	*line;

	signals_here_doc();
	close_pipe_struct(mini->pipes);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			free(delimiter);
			close(temp_file);
			exit(0);
		}
		write(temp_file, line, ft_strlen(line));
		free(line);
	}
}

int	process_here_doc(t_io_file *current, t_mini *mini)
{
	pid_t	pid;
	int		temp_file;
	char	*delimiter;
	int		status;

	delimiter = ft_strjoin(current->name, "\n");
	temp_file = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (temp_file == -1)
		return (free(delimiter), printf("Error opening temporal file\n"), 1);
	pid = fork();
	if (pid == 0)
		handle_here_doc_child(temp_file, delimiter, mini);
	wait(&status);
	free(delimiter);
	close(temp_file);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		unlink("/tmp/temp_file");
		mini->last_status = 130;
		return (1);
	}
	current->fd = open("/tmp/temp_file", O_RDONLY);
	if (current->fd == -1)
		return (unlink("/tmp/temp_file"), printf("Error opening file\n"), 1);
	return (0);
}
