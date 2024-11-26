/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 09:45:16 by miparis           #+#    #+#             */
/*   Updated: 2024/11/26 10:08:23 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>

# ifndef READ
#  define READ 0
# endif

# ifndef WRITE
#  define WRITE 1
# endif

typedef struct pipe
{
	bool	is_here_doc;
	int		infile;
	int		outfile;
	int		cmds_num;
	int		cmd_index;
	int		status;
	char	**arguments;
	char	**argv;
	int		old_pipe[2];
	int		new_pipe[2];
	pid_t	last_pid;
}				t_struct;

/*					Processes										*/
void	father(char **argv, char **envp);
void	first_child(int pipes[], char *argv[], char *envp[]);
void	second_child(int pipes[], char *argv[], char **envp);
pid_t	create_process(void);

/*					Paths & args									*/
char	*find_path(char *command, char *envp[]);
char	**retrieve_paths(char *envp[]);
char	*get_env_path(char *path, char *envp[]);
char	**get_args(char argv[]);

/*					BONUS											*/
/*				FILES & ARGS PROCESSING								*/
int		heredoc_mode(int argc, char *argv[], t_struct *t_struct, char *envp[]);
int		infile_mode(int argc, char *argv[], t_struct *t_struct, char *envp[]);
void	process_here_doc(char *argv[], t_struct *t_struct);

/*				PROCCESSES FUNCTIONS								*/
void	multiple_processes(t_struct *t_struct, char **envp, int argc);
void	first_process(t_struct *t_struct, char **envp);
void	middle_process(t_struct *t_struct, char **envp);
void	last_process(t_struct *t_struct, char **envp, int argc);
void	to_excve(t_struct *t_struct, char *argv[], char **envp);

/*				UTILS												*/
void	set_struct(t_struct *t_struct, char *argv[]);
void	set_cmds_num(t_struct *t_struct, int argc);
void	control(t_struct *t_struct);

#endif