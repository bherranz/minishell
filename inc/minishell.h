/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2024/10/22 12:53:08 by miparis          ###   ########.fr       */
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
	int 		index;
	char		*full_cmd;
	bool		simple; //comillas simples
	bool		doble; //comillas dobles
	bool		key; // caso {}
	char 		*e_input; //aqui iria el input a separar luego de expandir las variables
	char		*ex_var;
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
t_cmd 	*init_tcmd();
int		get_cmds(char const *s, char c, t_mini *mini);
int		is_quote(char c,  int *quote);
int		parse_cmds(t_mini *mini);
void	count_err(char *input);



/*				EXPANSOR				*/
int		get_var(t_mini *mini, t_cmd *cmd);
void	replace_var(t_cmd *cmd, char *str, char *e_str, char *str2);
char	*get_name(int i, char *cmd);
void 	do_expansion(char *name, t_mini *mini, t_cmd *cmd);
char 	*str_replace(char *str, const char *old, const char *new);
char 	*rest_str(int i, char *name, t_cmd cmd);
void	handle_expansor(t_mini *mini, t_cmd *cmd, char **str, char **str2, int i);

/*			UTILS					*/
void	print_error(char *msg, int perr, int err);
int		last_char(char str);


#endif
