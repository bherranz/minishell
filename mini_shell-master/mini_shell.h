/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:11:54 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:53:20 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define BUFFER_SIZE 777

enum
{
	I = 0,
	INDEX,
	FILE_INDEX,
};

typedef struct s_cmds
{
	char			*cmd;
	char			*path;
	char			*flags;
	int				trunc;
	int				here_doc;
	char			**infiles;
	char			**outfiles;
	int				fd_in;
	int				awk;
	int				tuvo[2];
}	t_cmds;

typedef struct s_mini_shell
{
	char				**envp;
	int					old_tubes[2];
	int					new_tubes[2];
	t_cmds				*cmds;
	int					num_cmds;
	pid_t				*childs;
	int					status;
	int					quote;
	struct sigaction	sig;
}	t_mini_shell;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	pid_t			pid;
}				t_sig;

int	g_id_signal;

///////////////////////////////////ENVP///////////////////////////////////
void	copy_envp(char **envp, t_mini_shell *ms);

///////////////////////////////////PARSE//////////////////////////////////
void	find_lines(char *txt, t_mini_shell *ms);
void	parse(char *txt, t_mini_shell *ms);
void	find_infile(char *txt, t_mini_shell *ms);
void	count_infiles(char *txt, t_mini_shell *ms);
void	find_outfile(char *txt, t_mini_shell *ms);
void	find_cmd(char *txt, t_mini_shell *ms);
void	heredoc(char *limitador, t_mini_shell *ms, int index);

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
int		ft_find_line(char *buff);
char	*gnl_strjoin(char *s1, char const *s2);
char	*gnl_substr(char const *s, unsigned int str, size_t len);
void	free_strs(char **strs);
void	skip_spaces(char *txt, int *i);

int		manage_quotes(char *txt, t_mini_shell *ms);
char	*clean_quotes(char *txt, t_mini_shell *ms);
char	*get_literal(char *txt, int *i);
int		skip_quotes(char *txt, char com);
char	*expand_variables(char *txt, t_mini_shell *ms);

///////////////////////////////////BUILTINS///////////////////////////////
int		do_builtins(char *txt, t_mini_shell *ms);
int		exec_builtin(char *txt, t_mini_shell *ms);

void	do_cd(char *txt, t_mini_shell *ms);
void	do_pwd(void);
void	do_envp(t_mini_shell *ms);
void	do_export(char *txt, t_mini_shell *ms);
void	do_unset(char *txt, t_mini_shell *ms);
void	do_echo(char *txt, t_mini_shell *ms);
void	do_exit(char *txt, t_mini_shell *ms);

///////////////////////////////////SEÑALES///////////////////////////////////
void	int_handler(int sig);
void	signal_ctlc_heredoc(int sig);

///////////////////////////////////PIPEX///////////////////////////////////

void	pipex(t_mini_shell *ms);
int		do_forks(t_mini_shell *ms);
int		open_outfiles(t_mini_shell *ms, int index);
int		open_infiles(t_mini_shell *ms, int index);
char	**alloc_awk(char **strs, t_mini_shell *ms, int child_index);
char	**do_awk(t_mini_shell *ms, int child_index);

//rutes
void	find_path(t_mini_shell *ms, int cmd_index);
char	**get_paths(t_mini_shell *ms);

//childs
void	do_one_child(t_mini_shell *ms);
void	do_first_child(t_mini_shell *ms);
void	do_middle_child(t_mini_shell *ms, int ci);
void	do_last_child(t_mini_shell *ms, int child_index);
void	exit_child(t_mini_shell *ms);

void	manage_fd_in(int *fd_in, t_mini_shell *ms, int child_index);
int		ft_valid_name_char(int c);

#endif