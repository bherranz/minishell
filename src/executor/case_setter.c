/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_setter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:12 by miparis           #+#    #+#             */
/*   Updated: 2024/11/27 12:40:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int	infile_mode(int argc, char *argv[], t_struct *t_struct, char *envp[])
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
}*/
int	process_here_doc(t_io_file *current)
{
	char	*line;
	int		temp_file;
	char	*delimiter;

	temp_file = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (temp_file == -1)
		return(printf("Error creando archivo temporal"), 1);
	delimiter = ft_strjoin(current->name, "\n");
	while (1)
	{
		write(1, "> ", 2); // Mostrar prompt
		line = get_next_line(0);
		if (!line)
			break; // Entrada estándar cerrada o error
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break;
		}
		write(temp_file, line, ft_strlen(line));
		free(line);
	}
	free(delimiter);
	close(temp_file);
	current->fd = open("/tmp/temp_file", O_RDONLY);
	return (0);
}
