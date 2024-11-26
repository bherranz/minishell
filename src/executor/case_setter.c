/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_setter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:12 by miparis           #+#    #+#             */
/*   Updated: 2024/11/26 10:09:18 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	infile_mode(int argc, char *argv[], t_struct *t_struct, char *envp[])
{
	if (argc >= 6)
	{
		set_struct(t_struct, argv);
		t_struct->infile = open(argv[1], O_RDONLY);
		multiple_processes(t_struct, envp, argc);
		return (0);
	}
	else
	{
		printf("Usage: infile cmd1 cmd2 cmd3 .... outfile\n");
		return (3);
	}
}

int	heredoc_mode(int argc, char *argv[], t_struct *t_struct, char *envp[])
{
	if (argc >= 6)
	{
		set_struct(t_struct, argv);
		process_here_doc(argv, t_struct);
		multiple_processes(t_struct, envp, argc);
		unlink("/tmp/temp_file");
		return (0);
	}
	else
	{
		printf("Usage: infile cmd1 cmd2 cmd3 .... outfile\n");
		return (3);
	}
}

void	process_here_doc(char *argv[], t_struct *t_struct)
{
	char	*line;
	int		temp_file;
	char	*delimiter;

	t_struct->is_here_doc = true;
	temp_file = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (temp_file == -1)
	{
		printf("Problem creating temp_file\n");
		exit (1);
	}
	delimiter = ft_strjoin(argv[2], "\n");
	printf("here_doc> \n");
	line = get_next_line(0);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(temp_file, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(delimiter);
	t_struct->infile = open("/tmp/temp_file", O_RDONLY, 0777);
	close(temp_file);
}
