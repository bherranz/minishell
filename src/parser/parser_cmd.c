/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/05 03:51:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// create list
// change space detection because now it's not detecting redirections not separated by spaces
// cat >output>output2

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
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble)) //->cambiar para que pille >/< como separador
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
	printf(" ===> TOKEN FOUND: %s\n", token);
	return (token);
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

void	print_list(t_io_file *list)
{
	while (list)
	{
		printf("%s ", list->name);
		list = list->next;
	}
	printf("\n");
}

void	list_addback(t_io_file *node, t_io_file **list)
{
	if (!list || !(*list))
	{
		list = malloc(sizeof(t_io_file));
		*list = node;
		printf("aa%s\n", (*list)->name);
		return ;
	}
	while ((*list)->next)
		*list = (*list)->next;
	(*list)->next = node;
}

t_io_file *create_redir(int redir_type, char *str, int *i, t_cmd *cmd)
{
	t_io_file	*redir;
	char		*file_token;

	redir = malloc(sizeof(t_io_file));
	if (!redir)
		return (NULL);
	file_token = get_token(&str[*(i + 1)], cmd);
	if (!file_token)
	{
		free(redir);
		return (NULL);
	}
	redir->type = redir_type;
	redir->name = file_token;
	if (redir->type < 3)
		list_addback(redir, &cmd->infile);
	else
		list_addback(redir, &cmd->outfile);
	print_list(cmd->infile);
	print_list(cmd->outfile);
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

int count_arguments(const char *str, t_cmd *cmd)
{
	int		i = 0;
    int		space = 0;
    bool	in_word = false;
	bool	is_redir = false;


	while (str[i])
	{
		process_quotes(str[i], cmd);
		if ((str[i] == '>' || str[i] == '<') && !in_word)
		{
			is_redir = true;
			i++;
		}
		if (!ft_isspace(str[i]) && !cmd->simple && !cmd->doble && !in_word 
				&& !is_redir)
		{
			space++;
			in_word = true;
		}
		else if (ft_isspace(str[i]) && !cmd->simple && !cmd->doble)
            in_word = false;
        i++;
    }
	return (space);
}

int main_cmd(char *str, t_cmd *cmd)
{
	int i;
	char *token;
	int space;
	int x;

	i = 0;
	space = 0;
	x = 0;
	cmd->simple = false;
	cmd->doble = false;
	//bucle para contar cuantos argumentos hay
	space = count_arguments(str, cmd);
	printf(" ------> Spaces = %i\n", space);
	cmd->args = malloc(sizeof(char *) * space);
	printf(" ------> Malloqueado = %i\n", space);
	while (str && str[i])
	{
		process_quotes(str[i], cmd);
		parse_redir(str, &i, cmd);
		if (!ft_isspace(str[i]))
		{
			token = get_token(&str[i], cmd);
			if (token)
			{
				cmd->args[x] = token;
				printf(" ===> ARG[%i]: %s\n", x, cmd->args[x]);
			}
			else
				return (-1);
			i += ft_strlen(token) - 1;
			free(token);
			x++;
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

/*NOTE - 
	is_redir = debe devolver el token encontrado y guardado como fd
	en is_redir = dependiendo de tipo de redireccion
	se guarda el type, y todo lo que hay después de la redirección como token para name
	es tomado como un fd (hasta el siguiente espacio 0 > / < )
	los fd deben ser guardados como nodo en el que tiene el nombre del archivo y un puntero al siguiente nodo
	desde i hasta la longitud del token debe ser salteado para seguir con el parseo
*/
