/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:33:36 by miparis           #+#    #+#             */
/*   Updated: 2024/11/19 11:33:14 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	list_addback(t_io_file *node, t_io_file **list)
{
	t_io_file	*tmp;

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

int	create_redir(int redir_type, char *str, int i, t_cmd *cmd)
{
	t_io_file	*redir;
	char		*file_token;
	char		*clean_name;

	redir = malloc(sizeof(t_io_file));
	if (!redir)
		return (-1);
	redir->type = redir_type;
	redir->next = NULL;
	if (str[i + 1] == str[i])
		file_token = get_token(&str[i + 2], cmd);
	else
		file_token = get_token(&str[i + 1], cmd);
	if (!file_token)
	{
		print_error("Error: syntax error near unexpected token `newline\'", "", 0, 258);
		return (free(redir), -1);
	}
	clean_name = clear_token(file_token, cmd, ft_strlen(file_token));
	if (!clean_name || is_redir(clean_name))
	{
		print_error("Error: syntax error near unexpected token ", clean_name, 0, 258);
		return (free(redir), free(file_token), -1);
	}
	redir->name = clean_name;
	if (redir->type < 3)
		list_addback(redir, &cmd->infile);
	else
		list_addback(redir, &cmd->outfile);
	return (0);
}

int	parse_redir(char *str, t_cmd *cmd)
{
	int		redir_type;
	int		i;

	i = 0;
    while (str[i])
	{
		process_quotes(str[i], cmd); // Actualizamos el estado de comillas para el carácter actual
		if (!(cmd->doble || cmd->simple))  // Si estamos fuera de comillas, verificamos redirecciones
		{
			redir_type = is_redir(&str[i]); // Detectamos si hay una redirección en la posición actual
			if (redir_type > 0)
			{
				if (create_redir(redir_type, str, i, cmd)) // Llamamos a create_redir para manejar la redirección
					return (-1);
				if (redir_type == 2 || redir_type == 4) // Avanzamos `i` según el tipo de redirección detectado
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
	return (0);
}
