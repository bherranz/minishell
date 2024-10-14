/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2024/10/10 12:35:27 by miparis          ###   ########.fr       */
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

extern int	g_signal; //global para señales

//los he puesto con nombres porque me parece más intuitivo
typedef enum e_type
{
	INFILE,
	HEREDOC,
	TRUNC,
	APPEND
}	t_type;

typedef struct s_io_file
{
	int		fd; //esto no sé si hará falta
	char	*file;
	t_type	type;
}	t_io_file;

typedef struct s_cmd
{
	char		*full_cmd;
	bool		simple; //comillas simples
	bool		doble; //comillas dobles
	bool		key; // caso {}
	char 		*e_input; //aqui iria el input a separar luego de expandir las variables
	char		**args;
	t_io_file	*infile;
	t_io_file	*outfile;
}	t_cmd;

typedef struct s_mini
{
	char	**envp;
	char	*input;
	int		here_doc;
	char	**cmds;
	int		pipes;
	t_cmd	**cmd; // comandos
	int		last_status;
}	t_mini;

/*			SIGNALS					*/
void	signals_handler(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

/*			PARSER					*/
void	parser(t_mini *mini);
int		check_quotes(t_mini *mini);
int		count_pipes(t_mini *mini);
int		tokenize(t_mini *mini);
int		get_cmds(char const *s, char c, t_mini *mini);
int		is_quote(char c,  int *quote);
/*void	print_cmd(t_mini *mini, int i);
int		pipe_count(t_mini *mini);*/



/*				EXPANSOR				*/
int		get_var(t_mini *mini, t_cmd *cmd);
void	replace_var(t_cmd *cmd, char *name, char *new_str);
char	*get_name(int i, char *cmd);
char *do_expansion(char *name, t_mini *mini);
char *str_replace(char *str, const char *old, const char *new);
char *replace_once(const char *str, const char *old, const char *new);

/*			UTILS					*/
void	print_error(char *msg, int perr, int err);
int		last_char(char str);


#endif
