/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:12 by miparis           #+#    #+#             */
/*   Updated: 2025/01/14 17:17:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_files(t_cmd *cmd, t_mini *mini)
{
	if (cmd->infile)
	{
		if (infiles(cmd->infile, mini))
			return (-1);
	}
	if (cmd->outfile)
	{
		if (outfiles(cmd->outfile, mini))
			return (-1);		
	}
	return (0);
}

int 	fd_control(t_io_file *current, t_mini *mini)
{
	if (current->fd == -1)
	{
		print_error("Error: no such file or directory: ", current->name, 0, 1);
		mini->last_status = 1;
		return (-1);
	}
	return (0);
}
int 	outfiles(t_io_file *outfiles, t_mini *mini)
{
	t_io_file 	*current;
	
	current = outfiles;
	while (current)
	{
		if (current->type == 3) // >
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_control(current, mini))
				return (-1);	
		}
		if (current->type == 4) // >> 
		{
			current->fd = open(current->name,  O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_control(current, mini))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

int 	infiles(t_io_file *infiles, t_mini *mini)
{
	t_io_file 	*current;
	
	current = infiles;
	while (current)
	{
		/*if (current->type == 2) // <<
		{
			if (process_here_doc(current))
				return (-1);
			if (fd_control(current, mini))
				return (-1);
			unlink("/tmp/temp_file"); //-> agregado por si quitan permisos
		}*/
		if (current->type == 1) // <
		{
			current->fd = open(current->name, O_RDONLY); // <
			if (fd_control(current, mini))
				return (-1);
		}
		current->last_in = (current->next == NULL);
		current = current->next;
	}
	return (0);
}

int	process_here_doc(t_io_file *current, t_mini *mini)
{
    pid_t   pid;
    int     temp_file;
    char    *delimiter;
    int     status;

    delimiter = ft_strjoin(current->name, "\n");
    temp_file = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (temp_file == -1)
    {
        free(delimiter);
        return (printf("Error creando archivo temporal\n"), 1);
    }
    pid = fork();
    if (pid == 0)
    {
        char *line;

		signals_here_doc();
        while (1)
        {
            write(1, "> ", 2);
            line = get_next_line(0);
            if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
            {
                free(line);
                free(delimiter);
                close(temp_file);
                exit(0); // Salir del proceso hijo al finalizar
            }
            write(temp_file, line, ft_strlen(line));
            free(line);
        }
    }
    waitpid(pid, &status, 0);
    free(delimiter);
    close(temp_file);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        unlink("/tmp/temp_file");
		mini->last_status = 130;
        return (1);
    }
    current->fd = open("/tmp/temp_file", O_RDONLY);
    if (current->fd == -1)
        return (printf("Error abriendo archivo temporal\n"), 1);
    return (0);
}
