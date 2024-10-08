/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/10/08 06:09:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(char *str)
{
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (3);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (4);
	return (0);
}

int	main_cmd(char *str, t_cmd *cmd)
{
	char	*token;
	(void)token;
	(void)cmd;
	// cmd->args = malloc(sizeof(char) * ft_strlen(str));
	// cmd->infile = malloc(sizeof(t_io_file) * ft_strlen(str));
	// cmd->outfile= malloc(sizeof(t_io_file) * ft_strlen(str));
	printf("str: %s\n", str);
	if (str)
		printf("espacio: %i\n", ft_isspace(str[0]));
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int i;

	//para los infiles y outfiles guardar sin comillas, para los comandos, investigar
	i = 0;
	printf("command: %s\n", mini->cmd[0]->full_cmd);
	while (i <= mini->pipes)
	{
		printf("command: %s\n", mini->cmd[0]->full_cmd);
		printf("command %i\n", i);
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
		 	return (-1);
		//printf("error %i\n", main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]));
		i++;
	}
	return (0);
}
