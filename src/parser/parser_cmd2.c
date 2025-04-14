/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:46:14 by codespace         #+#    #+#             */
/*   Updated: 2025/01/19 13:08:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*clear_token(char *str, t_cmd *cmd, int len)
{
	char	*clean_token;
	int		clean_index;
	int		i;

	clean_index = 0;
	i = 0;
	clean_token = ft_calloc(len + 1, sizeof(char));
	cmd->simple = false;
	cmd->doble = false;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if ((str[i] == '\'' && !cmd->doble) || (str[i] == '"'
					&& !cmd->simple))
				process_quotes(str[i], cmd);
			else
				clean_token[clean_index++] = str[i];
		}
		else
			clean_token[clean_index++] = str[i];
		i++;
	}
	clean_token[clean_index] = '\0';
	return (clean_token);
}

int	process_redirections(char *str, int *end, int start, t_cmd *cmd)
{
	if ((str[*end] != '\'' && str[*end] != '"') && !cmd->simple
		&& !cmd->doble && (str[*end] == '<' || str[*end] == '>'))
	{
		if (*end == start)
		{
			if (str[*end + 1] == str[*end])
				(*end)++;
			(*end)++;
		}
		return (1);
	}
	return (0);
}

char	*get_token(char *str, t_cmd *cmd)
{
	int		start;
	int		end;
	char	*token;

	start = 0;
	while (ft_isspace(str[start]))
		start++;
	end = start;
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble))
	{
		process_quotes(str[end], cmd);
		if (process_redirections(str, &end, start, cmd))
			break ;
		end++;
	}
	if (end == start)
		return (NULL);
	token = ft_substr(str, start, end - start);
	return (token);
}

void	process_quotes(char c, t_cmd *cmd)
{
	if (c == '\'')
	{
		if (!cmd->doble)
			cmd->simple = !cmd->simple;
	}
	else if (c == '"')
	{
		if (!cmd->simple)
			cmd->doble = !cmd->doble;
	}
}
