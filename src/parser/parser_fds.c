/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:33:36 by miparis           #+#    #+#             */
/*   Updated: 2025/01/19 15:16:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_clean_token(char *str, int i, t_cmd *cmd)
{
	char	*file_token;
	char	*clean_name;

	if (str[i + 1] == str[i])
		file_token = get_token(&str[i + 2], cmd);
	else
		file_token = get_token(&str[i + 1], cmd);
	if (!file_token)
	{
		print_error("Error: syntax error near unexpected token 'newline'",
			"", 0, 258);
		return (NULL);
	}
	clean_name = clear_token(file_token, cmd, ft_strlen(file_token));
	free(file_token);
	return (clean_name);
}

int	create_redir(int redir_type, char *str, int i, t_cmd *cmd)
{
	t_io_file	*redir;
	char		*clean_name;

	redir = malloc(sizeof(t_io_file));
	if (!redir)
		return (-1);
	redir->type = redir_type;
	redir->next = NULL;
	redir->fd = -1;
	clean_name = get_clean_token(str, i, cmd);
	if (!clean_name)
		return (free(redir), -1);
	if (is_redir(clean_name))
	{
		print_error("Error: syntax error near unexpected token ",
			clean_name, 0, 258);
		return (free(redir), free(clean_name), -1);
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
	cmd->simple = false;
	cmd->doble = false;
	while (str[i])
	{
		process_quotes(str[i], cmd);
		if (!(cmd->doble || cmd->simple))
		{
			redir_type = is_redir(&str[i]);
			if (redir_type > 0)
			{
				if (create_redir(redir_type, str, i, cmd))
					return (-1);
				if (redir_type == 2 || redir_type == 4)
					i += 1;
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}
