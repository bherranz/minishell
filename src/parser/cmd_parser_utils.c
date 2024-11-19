/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:28:34 by miparis           #+#    #+#             */
/*   Updated: 2024/11/19 11:29:25 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_quotes(char c, t_cmd *cmd)
{
	if (c == '\'')
		cmd->simple = !cmd->simple;
	else if (c == '"')
		cmd->doble = !cmd->doble;
}


char *clear_token(char *str, t_cmd *cmd, int len)
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
			if ((str[i] == '\'' && !cmd->doble) || (str[i] == '"' && !cmd->simple))
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
