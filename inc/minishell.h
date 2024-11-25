/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2024/11/25 06:59:41 by codespace        ###   ########.fr       */
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

typedef enum e_type
{
	INFILE,
	HEREDOC,
	TRUNC,
	APPEND
}	t_type;

typedef struct s_io_file
{
	int					fd; //esto no sé si hará falta
	char				*name;
	t_type				type;
	struct s_io_file	*next;
}	t_io_file;

//ver donde ponemos referencias de stdin y stdout

typedef struct s_cmd
{
	int 		index;
	char		*full_cmd;
	bool		simple; //comillas simples
	bool		doble; //comillas dobles
	char 		*e_input;
	char		*ex_var;
	char		**args;
	t_io_file	*infile; //->tiene que ser doble
	t_io_file	*outfile; //-> Same as above
}	t_cmd;

typedef struct s_mini
{
	char	**envp;
	char	*input;
	int		here_doc;
	char	**cmds;
	int		pipes;
	t_cmd	**cmd;
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
int		parse_cmds(t_mini *mini);
void	count_err(char *input);

/*				EXPANSOR				*/
int		expand(t_mini *mini, t_cmd *cmd);
void	replace_input(t_cmd *cmd, char *str, char *e_str, char *str2);
char	*get_var(int i, char *cmd);
void	do_expansion(char *name, t_mini *mini, t_cmd *cmd);
char	*rest_str(int i, char *name, t_cmd cmd);
void	handle_expansion(t_mini *mini, t_cmd *cmd, char **str2, int i);



/*				PARSER CMD										 */
int			parse_cmds(t_mini *mini);
int			main_cmd(char *str, t_cmd *cmd);
void		process_quotes(char c, t_cmd *cmd);
char		*get_token(char *str, t_cmd *cmd);
void 		skip_not_args(char *str, int *i, t_cmd *cmd);
int 		count_arguments(char *str, t_cmd *cmd);
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

#endif