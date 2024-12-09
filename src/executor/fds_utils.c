/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:12 by miparis           #+#    #+#             */
/*   Updated: 2024/12/09 10:52:15 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_files(t_cmd *cmd)
{
	if (cmd->infile)
	{
		print_list(cmd->infile);
		if (infiles(cmd->infile))
			return (-1);
	}
	if (cmd->outfile)
	{
		print_list(cmd->outfile);
		if (outfiles(cmd->outfile))
			return (-1);		
	}
	return (0);
}

int 	fd_control(t_io_file *current)
{
	if (current->fd == -1)
	{
		print_error("Error: no such file or directory: ", current->name, 0, 258);
		return (1);
	}
	return (0);
}
int 	outfiles(t_io_file *outfiles)
{
	t_io_file 	*current;
	
	current = outfiles;
	while (current)
	{
		if (current->type == 3) // >
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_control(current))
				return (-1);	
		}
		if (current->type == 4) // >> 
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_control(current))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

int 	infiles(t_io_file *infiles)
{
	t_io_file 	*current;
	
	current = infiles;
	while (current)
	{
		if (current->type == 2) // <<
		{
			if (process_here_doc(current))
				return (-1);
			if (fd_control(current))
				return (-1);
			unlink("/tmp/temp_file"); //-> agregado por si quitan ppermisos
		}
		else
		{
			current->fd = open(current->name, O_RDONLY); // <
			if (fd_control(current))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

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
