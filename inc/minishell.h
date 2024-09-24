/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/24 05:49:05 by codespace        ###   ########.fr       */
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
	char		*cmd;
	char		**args;
	t_io_file	*infile;
	t_io_file	*outfile;
}	t_cmd;

typedef struct s_mini
{
	char	**envp;
	char	*input;
	int		here_doc;
	t_cmd	*cmd;
	int		simple; //comillas simples
	int		doble; //comillas dobles
	int		last_status;
}	t_mini;

/*			SIGNALS					*/
void	signals_handler(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

/*			PARSER					*/
void	parser(t_mini *mini);

/*			UTILS					*/
void	print_error(char *msg, int perr, int err);

#endif
