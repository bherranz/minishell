/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2025/02/10 17:30:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdbool.h>
# include <termcap.h>
# include <string.h>
# include "../libft/libft.h"

# ifndef READ
#  define READ 0
# endif

# ifndef WRITE
#  define WRITE 1
# endif
# include <limits.h>
# include <errno.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern int	g_signal; //global para señales

typedef struct s_pipe
{
	int		cmds_num;
	int		cmd_index;
	int		status;
	int		old_pipe[2];
	int		new_pipe[2];
	pid_t	last_pid;
}				t_pipe;

typedef enum e_type
{
	INFILE,
	HEREDOC,
	TRUNC,
	APPEND
}	t_type;

typedef struct s_io_file
{
	int					fd;
	char				*name;
	t_type				type;
	bool				last_in;
	struct s_io_file	*next;
}	t_io_file;

typedef struct s_cmd
{
	int			index;
	char		*full_cmd;
	bool		simple; //comillas simples
	bool		doble; //comillas dobles
	char		*e_input;
	char		*ex_var;
	char		**args;
	t_io_file	*infile; //->tiene que ser doble
	t_io_file	*outfile; //-> Same as above
}	t_cmd;

typedef struct s_mini
{
	int		stdin;
	int		stdout;
	char	**envp;
	char	*input;
	int		here_doc;
	char	**cmds;
	int		pipes_n;
	t_pipe	*pipes;
	t_cmd	**cmd;
	int		last_status;
}	t_mini;

/*			SIGNALS					*/
void		signals_handler(void);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		no_see_ctrlC(void);
void		signals_here_doc(void);

/*			PARSER					*/
int			parser(t_mini *mini);
void		init_mini(t_mini *mini);
int			check_quotes(t_mini *mini);
int			count_pipes(t_mini *mini);
int			tokenize(t_mini *mini);
int			get_cmds(char const *s, char c, t_mini *mini);
int			is_quote(char c, int *quote);
int			parse_cmds(t_mini *mini);
int			count_err(char *input);

/*				SET ENVP				*/
void		set_envp(t_mini *mini, char **envp);
void		unset_shlvl(char **envp);
char		*shell_level(char *envp, int start);
void		env_print_shlvl(char *shlvl);

/*				EXPANSOR				*/
int			expand(t_mini *mini, t_cmd *cmd);
void		replace_input(t_cmd *cmd, char *str, char *e_str, char *str2);
char		*get_var(int i, char *cmd);
void		do_expansion(char *name, t_mini *mini, t_cmd *cmd);
char		*rest_str(int i, char *name, t_cmd cmd);
void		handle_expansion(t_mini *mini, t_cmd *cmd, char **str2, int i);

/*				PARSER CMD										 */
int			parse_cmds(t_mini *mini);
int			main_cmd(char *str, t_cmd *cmd);
void		process_quotes(char c, t_cmd *cmd);
char		*get_token(char *str, t_cmd *cmd);
void		skip_not_args(char *str, int *i, t_cmd *cmd);
void		count_arguments(char *str, t_cmd *cmd, int *count);
void		add_arg_to_cmd(t_cmd *cmd, char *arg);
char		*clear_token(char *str, t_cmd *cmd, int len);

/*				PARSER REDIR										 */
int			parse_redir(char *str, t_cmd *cmd);
int			create_redir(int redir_type, char *str, int i, t_cmd *cmd);
void		list_addback(t_io_file *node, t_io_file **list);
t_io_file	*check_file_quotes(t_io_file *node);
void		print_list(t_io_file *list);
int			is_redir(char *str);

/*										UTILS					*/
void		print_error(char *msg, char *var, int perr, int err);
int			last_char(char str);
t_cmd		*init_tcmd(void);
void		free_array(char **array);
void		free_io_files(t_io_file *file_list);
void		free_structs(t_mini *mini);
void		close_std_fd(t_mini *mini);
int			new_input(t_mini *mini);

/* 					EXECUTOR									*/
void		executor(t_mini *mini);
int			open_files(t_cmd *cmd, t_mini *mini);
int			infiles(t_io_file *infiles, t_mini *mini);
int			outfiles(t_io_file *outfiles, t_mini *mini);
int			fd_control(t_io_file *current, t_mini *mini);
int			process_here_doc(t_io_file *current, t_mini *mini);
void		try_open(t_cmd *cmd, t_mini *mini);

void		multiple_processes(t_cmd *cmd, t_mini *mini, t_pipe *pipe);
void		set_struct(t_pipe *t_struct);
void		set_cmds_num(t_pipe *t_struct, int argc);
int			control(t_pipe *pipe);
void		first_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini);
void		middle_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini);
void		last_process(t_cmd *cmd, t_pipe *pipes, t_mini *mini);
void		one_cmd(t_cmd *cmd, t_mini *mini);
void		single_process(t_cmd *cmd, t_mini *mini);
void		to_excve(t_cmd *cmd, t_mini *mini);
pid_t		create_process(void);

void		close_fds(t_io_file *fds);
void		replace_dup2(t_io_file *fds, int pipe_fd, int type, t_mini *mini);
void		create_pipe(t_pipe *pipes);
void		process_status(t_pipe *pipes, t_mini *mini);
void		close_pipe_struct(t_pipe *pipes);

//Paths & args									
char		*find_path(char *command, char *envp[]);
char		**retrieve_paths(char *envp[]);
char		*get_env_path(char *path, char *envp[]);

/*						BUILT-INS					*/
void		main_builtins(t_cmd *cmd, t_mini *mini);
int			is_builtin(char *cmd);
void		ft_echo(t_cmd *cmd, t_mini *mini);
void		ft_cd(t_cmd *cmd, char **envp, t_mini *mini);
int			cd_hyphen(char **envp, t_mini *mini);
char		*ft_getenv(char *name, char **envp);
int			update_pwd(char **envp, t_mini *mini);
char		*ft_getenv(char *name, char **envp);
void		ft_pwd(t_mini *mini);
void		ft_env(char **envp, t_cmd *cmd, t_mini *mini);
void		ft_export(t_mini *mini, char **var);
void		print_export(char **envp);
int			check_var(char *var, t_mini *mini);
void		ft_exit(t_mini *mini, char **var);
void		ft_unset(t_mini *mini, char **var);
char		**new_envp(int count, t_mini *mini, char **var);

#endif
