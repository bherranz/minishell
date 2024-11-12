/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/12 11:07:56 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_token(char *str, t_cmd *cmd)
{
	int start;
	int end;
	char *token;

	start = 0;
	while (ft_isspace(str[start]))  // saltar espacios iniciales
		start++;
	end = start;
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble))
	{
		if (str[end] == '\'')
			cmd->simple = !cmd->simple;
		else if (str[end] == '"')
			cmd->doble = !cmd->doble;
		else if (!cmd->simple && !cmd->doble && (str[end] == '<' || str[end] == '>'))
		{
			if (end == start) // Si el redireccionamiento está al principio
			{
				if (str[end + 1] == str[end]) // Manejar << o >>
					end++;
				end++;
			}
			break;
		}
		end++;
	}
	if (end == start)
		return NULL;
	token = ft_substr(str, start, end - start);
	return (token);
}

int	is_redir(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (4);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (3);
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

t_io_file	*check_file_quotes(t_io_file *node)
{
	if (!node)
		return (NULL);
	if (node->name[0] == '\'' || node->name[0] == '"')
		node->name = ft_substr(node->name, 1, ft_strlen(node->name) - 2);
	return (node);
}

void	list_addback(t_io_file *node, t_io_file **list)
{
	t_io_file	*tmp;

	node = check_file_quotes(node);
	if (!list || !node)
		return ;
	if (!(*list))
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	create_redir(int redir_type, char *str, int i, t_cmd *cmd)
{
	t_io_file *redir;
	char *file_token;

	redir = malloc(sizeof(t_io_file));
	if (!redir)
		return ;
	redir->type = redir_type;
	redir->next = NULL;
	if (str[i + 1] == str[i])
		file_token = get_token(&str[i + 2], cmd);
	else
		file_token = get_token(&str[i + 1], cmd);
	if (!file_token)
	{
		free(redir);
		return ;
	}
	redir->name = file_token;
	if (redir->type < 3)
		list_addback(redir, &cmd->infile);
	else
		list_addback(redir, &cmd->outfile);
}
/*
void	parse_redir(char *str, t_cmd *cmd)
{
	int	redir_type;
	int i;

	i = 0;
	while (str[i])
	{
		//-> tiene que tomarlo como redir si no esta entre comillas
		process_quotes(str[i], cmd);
		if (cmd->doble || cmd->simple)
			return ;
		redir_type = is_redir(&str[i]);
		if (redir_type > 0)
		{
			create_redir(redir_type, str, i, cmd);
			if (redir_type == 2 || redir_type == 4)
				i++;
		}
		i++;
	}
}*/

void parse_redir(char *str, t_cmd *cmd)
{
    int redir_type;
    int i = 0;

    while (str[i])
	{
        // Actualizamos el estado de comillas para el carácter actual
        process_quotes(str[i], cmd);

        // Si estamos fuera de comillas, verificamos redirecciones
        if (!(cmd->doble || cmd->simple))
		{
            // Detectamos si hay una redirección en la posición actual
            redir_type = is_redir(&str[i]);
            if (redir_type > 0)
			{
                // Llamamos a create_redir para manejar la redirección
                create_redir(redir_type, str, i, cmd);

                // Avanzamos `i` según el tipo de redirección detectado
                if (redir_type == 2 || redir_type == 4)
                    i += 2; // Avanzar dos posiciones para `<<` o `>>`
                else
                    i += 1; // Avanzar una posición para `<` o `>`
            } 
			else
                i++;
        } 
		else
            i++;
    }
}


void	process_quotes(char c, t_cmd *cmd)
{
	if (c == '\'')
		cmd->simple = !cmd->simple;
	else if (c == '"')
		cmd->doble = !cmd->doble;
}
/*void	process_quotes(char c, t_cmd *cmd)
{

	if (c == '\'' && !cmd->simple)
		cmd->simple = !cmd->simple;
	else if (c == '"' && !cmd->simple)
		cmd->doble = !cmd->doble;
}*/

void skip_not_args(char *str, int *i, t_cmd *cmd)
{
	//para malloc funciona okay
	printf("--> SKIP NOT ARGS\n");
    while (ft_isspace(str[*i]))
        (*i)++;
   // process_quotes(str[*i], cmd);
    while ((str[*i] == '<' || str[*i] == '>') || (cmd->simple || cmd->doble))
    {
        if (str[*i + 1] == str[*i])
            (*i) += 2;
        else
            (*i)++;
        while (ft_isspace(str[*i]))
            (*i)++;
        while (str[*i] && (!ft_isspace(str[*i]) || cmd->simple || cmd->doble) && str[*i] != '<' && str[*i] != '>')
        {
            process_quotes(str[*i], cmd);
            (*i)++;
        }
        while (ft_isspace(str[*i]))
            (*i)++;
    }
}

void skip_not_args2(char *str, int *i, t_cmd *cmd)
{
	printf("--> SKIP NOT ARGS2\n");
     while (ft_isspace(str[*i]))
        (*i)++;
    process_quotes(str[*i], cmd);
    while ((str[*i] == '<' || str[*i] == '>') || (cmd->simple || cmd->doble))
    {
        if (str[*i + 1] == str[*i])
            (*i) += 2;
        else
            (*i)++;
        while (ft_isspace(str[*i]))
            (*i)++;
        while (str[*i] && (!ft_isspace(str[*i]) || cmd->simple || cmd->doble) && str[*i] != '<' && str[*i] != '>')
        {
            process_quotes(str[*i], cmd);
            (*i)++;
        }
        while (ft_isspace(str[*i]))
            (*i)++;
    }
}

int count_arguments(char *str, t_cmd *cmd)
{
    int count = 0;
    char *token;
    int i = 0;

    while (str[i])
    {
		skip_not_args(str, &i, cmd);
		printf("str: %s\n", &str[i]);
        if (str[i])
        {
            token = get_token(&str[i], cmd);
            if (token)
            {
                count++;
                i += ft_strlen(token) - 1;
                free(token);
            }
			i++;
        }
    }
    return count;
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
	space = count_arguments(str, cmd);
	printf(" ------> Spaces = %i\n", space);
	cmd->args = malloc(sizeof(char *) * space);
	printf(" ------> Malloqueado = %i\n", space);
	parse_redir(str, cmd);
	printf("Infiles: ");
	print_list(cmd->infile);
	printf("Outfiles: ");
	print_list(cmd->outfile);
	while (str && str[i])
	{
		printf("----> HELLOU\n");
		skip_not_args2(str, &i, cmd);
		printf("----> i = %d\n", i);
		if (str[i])
		{
			printf("---> IF TOKEN\n");
			token = get_token(&str[i], cmd);
			if (token)
			{
				cmd->args[x] = token;
				printf("ARG[%i] = %s\n", x, cmd->args[x]);
				x++;
				i += ft_strlen(token) - 1;
			}
			i++;
		}
	}
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int i;

	i = 0;
	while (i <= mini->pipes)
	{
		printf("command: %s\n", mini->cmd[i]->full_cmd);
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
		 	return (-1);
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
