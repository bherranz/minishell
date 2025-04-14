/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2025/01/19 12:34:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	count_arguments(char *str, t_cmd *cmd, int *count)
{
	char	*token;
	int		i;
	char	*clean;

	i = 0;
	while (str[i])
	{
		skip_not_args(str, &i, cmd);
		if (!str[i])
			break ;
		token = get_token(&str[i], cmd);
		if (!token)
			break ;
		clean = clear_token(token, cmd, ft_strlen(token));
		if (clean)
		{
			(*count)++;
			i += ft_strlen(token) - 1;
			free(clean);
		}
		free(token);
		i++;
	}
}

void	process_arguments(char *str, t_cmd *cmd)
{
	int		i;
	int		x;
	char	*token;
	char	*clean;

	i = 0;
	x = 0;
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
				cmd->args[x++] = clean;
				i += ft_strlen(token) - 1;
			}
			free(token);
			i++;
		}
	}
}

int	main_cmd(char *str, t_cmd *cmd)
{
	int		space;

	space = 0;
	count_arguments(str, cmd, &space);
	cmd->args = ft_calloc(space + 1, sizeof(char *));
	if (parse_redir(str, cmd))
		return (-1);
	process_arguments(str, cmd);
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int	i;

	i = 0;
	while (i <= mini->pipes_n)
	{
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}
