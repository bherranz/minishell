/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:38 by bherranz          #+#    #+#             */
/*   Updated: 2024/09/23 10:09:43 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
#include <readline/history.h>
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

int g_signal; //global para señales

//tenemos que decidir la estructura
typedef struct s_mini
{
	char	**envp;
	//temporal
	char	*input;
}	t_mini;
















/*			SIGNALS					*/
void	signals_handler();
void	sigint_handler(int sig);
void	sigquit_handler(int sig);


#endif
