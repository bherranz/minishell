/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/10/23 09:03:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_token(char *str, t_cmd *cmd)
{
	int		start;
	int		end;
	char	*token;

	start = 0;
	end = 0;
	cmd->simple = false;
	cmd->doble = false;
	while (ft_isspace(str[start]))  // saltar espacios iniciales
		start++;
	end = start;
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble))
	{
		if (str[end] == '\'')
			cmd->simple = !cmd->simple;
		else if (str[end] == '"')
			cmd->doble = !cmd->doble;
		end++;
	}
	if (end == start)
		return NULL;
	token = (char *)malloc(end - start + 1);
	if (!token)
		return NULL;
	ft_strlcpy(token, &str[start], end - start + 1);
	token[end - start] = '\0';
	printf("token: %s\n", token);
	return (token);
}

void add_arg_to_cmd(t_cmd *cmd, char *token)
{
	char **new_args;
	int i = 0;

	if (!token)
		return;
	new_args = malloc(sizeof(char *) * (cmd->index + 2)); // +2 para el nuevo token y NULL
	if (!new_args)
		return;
	while (i < cmd->index)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = token;
	cmd->index++;
	new_args[cmd->index] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

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

t_io_file *create_redir(int redir_type, char *str, int *i, t_cmd *cmd)
{
	t_io_file	*redir;
	char		*file_token;

	redir = malloc(sizeof(t_io_file));
	if (!redir)
		return (NULL);
	file_token = get_token(&str[*i], cmd);
	if (!file_token)
	{
		free(redir);
		return (NULL);
	}
	redir->type = redir_type;
	redir->file = file_token;
	return (redir);
}
//falta hacerlo para varios en el mismo comando
// cambiar estructura infile outfile a array, poner un índice
void	parse_redir(char *str, int *i, t_cmd *cmd)
{
	int	redir_type;

	redir_type = is_redir(&str[*i]);
	if (redir_type > 0)
	{
		if (redir_type == 1 || redir_type == 2) // "<" o "<<"
			cmd->infile = create_redir(redir_type, str, i, cmd);
		else if (redir_type == 3 || redir_type == 4) // ">" o ">>"
			cmd->outfile = create_redir(redir_type, str, i, cmd);
	}
}

void	process_quotes(char c, t_cmd *cmd)
{
	if (c == '\'')
		cmd->simple = !cmd->simple;
	else if (c == '"')
		cmd->doble = !cmd->doble;
}

int main_cmd(char *str, t_cmd *cmd)
{
	int i;
	char *token;

	i = 0;
	while (str[i])
	{
		process_quotes(str[i], cmd);
		parse_redir(str, &i, cmd);
		if (!ft_isspace(str[i]))
		{
			token = get_token(&str[i], cmd);
			//hacer un bucle para contar cuantos argumentos hay
			//malloc
			//separar argumentos y guardarlos
			if (token)
				add_arg_to_cmd(cmd, token);
			else
				return (-1);
			i += ft_strlen(token);
		}
		i++;
	}
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int i;

	//para los infiles y outfiles guardar sin comillas, para los comandos, investigar
	i = 0;
	while (i <= mini->pipes)
	{
		printf("command: %s\n", mini->cmd[i]->full_cmd);
		printf("command %i\n", i);
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
		 	return (-1);
		//printf("error %i\n", main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]));
		i++;
	}
	return (0);
}
