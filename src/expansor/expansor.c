/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:40:02 by miparis           #+#    #+#             */
/*   Updated: 2025/02/10 17:32:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand(t_mini *mini, t_cmd *cmd)
{
	size_t	i;
	char	*str2;

	i = 0;
	str2 = NULL;
	while (cmd->full_cmd[i])
	{
		if (cmd->full_cmd[i] == '\'' && !cmd->doble)
			cmd->simple = !cmd->simple;
		if (cmd->full_cmd[i] == '\"' && !cmd->simple)
			cmd->doble = !cmd->doble;
		if (cmd->full_cmd[i] == '$'
			&& (!cmd->simple || (cmd->simple && cmd->doble)))
			handle_expansion(mini, cmd, &str2, i);
		if (i < ft_strlen(cmd->full_cmd))
			i++;
		else
			break ;
	}
	if (cmd->simple == 1)
		cmd->simple = !cmd->simple;
	return (0);
}

void	replace_input(t_cmd *cmd, char *str, char *e_str, char *str2)
{
	char	*aux;

	if (e_str)
	{
		if (cmd->doble || !cmd->simple)
		{
			free(cmd->full_cmd);
			cmd->full_cmd = ft_strjoin(str, e_str);
		}
		if (str2 != NULL)
		{
			aux = cmd->full_cmd;
			cmd->full_cmd = ft_strjoin(aux, str2);
			free(aux);
		}
	}
	else
	{
		aux = cmd->full_cmd;
		if (str2 != NULL)
			cmd->full_cmd = ft_strjoin(str, str2);
		else
			cmd->full_cmd = ft_strdup(str);
		free(aux);
	}
}

char	*get_var(int i, char *cmd)
{
	char	*name;
	int		start;
	int		name_len;

	start = i;
	name_len = 0;
	while (cmd[i] && (ft_isalnum(cmd[i]) == 1 || cmd[i] == '_'))
	{
		name_len++;
		i++;
	}
	name = ft_substr(cmd, start, name_len);
	if (!name)
	{
		printf("Name not found\n");
		return (NULL);
	}
	return (name);
}

void	do_expansion(char *name, t_mini *mini, t_cmd *cmd)
{
	int		x;

	x = 0;
	if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
		cmd->e_input = (ft_itoa(mini->last_status));
	if (!name)
		return ;
	while (mini->envp[x])
	{
		if (ft_strncmp(name, mini->envp[x], ft_strlen(name)) == 0)
		{
			if (ft_strchr(mini->envp[x], '='))
				cmd->e_input = ft_strdup((ft_strrchr(mini->envp[x], '=') + 1));
			return ;
		}
		x++;
	}
	if (!cmd->e_input)
		cmd->e_input = NULL;
}

void	handle_expansion(t_mini *mini, t_cmd *cmd, char **str2, int i)
{
	char	*str;

	str = ft_substr(cmd->full_cmd, 0, i);
	if (cmd->full_cmd[i + 1] == '?')
	{
		cmd->ex_var = ft_strdup("$?");
		*str2 = rest_str(i, cmd->ex_var, *cmd);
		do_expansion(cmd->ex_var, mini, cmd);
		replace_input(cmd, str, cmd->e_input, *str2);
	}
	else if (cmd->full_cmd[i + 1] == ' ' || cmd->full_cmd[i + 1] == '\0')
	{
		cmd->ex_var = ft_strdup("$");
		*str2 = rest_str(i, cmd->ex_var, *cmd);
		replace_input(cmd, str, cmd->e_input, *str2);
	}
	else if (cmd->full_cmd[i + 1] != '\0')
	{
		cmd->ex_var = get_var(i + 1, cmd->full_cmd);
		*str2 = rest_str(i, cmd->ex_var, *cmd);
		do_expansion(cmd->ex_var, mini, cmd);
		replace_input(cmd, str, cmd->e_input, *str2);
	}
	return (free(str), free(*str2), free(cmd->ex_var));
}
