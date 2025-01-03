/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2025/01/03 16:32:24 by codespace        ###   ########.fr       */
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

char	*get_token(char *str, t_cmd *cmd)
{
	int		start;
	int		end;
	char	*token;

	start = 0;
	while (ft_isspace(str[start])) // saltar espacios iniciales
		start++;
	end = start;
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble))
	{
		process_quotes(str[end], cmd);
		if ((str[end] != '\'' && str[end] != '"') && !cmd->simple && !cmd->doble
			&& (str[end] == '<' || str[end] == '>'))
		{
			if (end == start) // Si el redireccionamiento está al principio
			{
				if (str[end + 1] == str[end]) // Manejar << o >>
					end++;
				end++;
			}
			break ;
		}
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

void	skip_not_args(char *str, int *i, t_cmd *cmd)
{
	cmd->simple = false;
	cmd->doble = false;
	while (ft_isspace(str[*i]))
		(*i)++;
	while (str[*i] && ((str[*i] == '<' || str[*i] == '>')
			|| (cmd->simple || cmd->doble)))
	{
		if (str[*i + 1] && (str[*i + 1] == str[*i]))
			(*i) += 2;
		else
			(*i)++;
		if (!str[*i])
			break ;
		while (ft_isspace(str[*i]))
			(*i)++;
		while (str[*i] && (!ft_isspace(str[*i]) || cmd->simple || cmd->doble)
			&& str[*i] != '<' && str[*i] != '>')
		{
			process_quotes(str[*i], cmd);
			(*i)++;
		}
		while (ft_isspace(str[*i]))
			(*i)++;
	}
}

int	count_arguments(char *str, t_cmd *cmd)
{
	int		count;
	char	*token;
	int		i;
	char	*clean;

	count = 0;
	i = 0;
	while (str[i])
	{
		skip_not_args(str, &i, cmd);
		if (str[i])
		{
			token = get_token(&str[i], cmd);
			if (!token)
				break ;
			clean = clear_token(token, cmd, ft_strlen(token));
			if (clean)
			{
				count++;
				i += ft_strlen(token) - 1;
				free(token);
				free(clean);
			}
			i++;
		}
	}
	return (count);
}

int	main_cmd(char *str, t_cmd *cmd)
{
	int		i;
	char	*token;
	int		space;
	int		x;
	char	*clean;

	i = 0;
	space = 0;
	x = 0;
	space = count_arguments(str, cmd);
	cmd->args = malloc(sizeof(char *) * (space + 1));
	cmd->args[space] = NULL;
	if (parse_redir(str, cmd))
		return (-1);
	while (str && str[i])
	{
		skip_not_args(str, &i, cmd);
		if (str[i])
		{
			token = get_token(&str[i], cmd);
			if (!token || !*token)
				break ;
			clean = clear_token(token, cmd, ft_strlen(token));
			if (clean)
			{
				cmd->args[x] = clean;
				x++;
				i += ft_strlen(token) - 1;
				free(token);
			}
			i++;
		}
	}
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int	i;

	i = 0;
	while (i <= mini->pipes)
	{
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}
