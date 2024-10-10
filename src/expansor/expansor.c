/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:40:02 by miparis           #+#    #+#             */
/*   Updated: 2024/10/10 12:36:25 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_var(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*new_str;
	char	*name;

	i = 0;
	cmd->simple = false;
	cmd->doble = false;
	cmd->key = false;
	new_str = NULL;
	while (cmd->full_cmd[i])
	{
		if (cmd->full_cmd[i] == '\'')
			cmd->simple = !cmd->simple;
		if (cmd->full_cmd[i] == '$' && !cmd->simple)
		{
			if (cmd->full_cmd[i] == '?')
			{
				name = "$?";
				new_str = do_expansion(name, mini);
			}
			else
			{
				name = get_name(i, cmd);
				new_str = do_expansion(name, mini);
			}
		}
		i++;
	}
	replace_var(cmd, name, new_str);
	printf("Cadena con expansion: %s\n", cmd->full_cmd);
	return (0);
}

void	replace_var(t_cmd *cmd, char *name, char *new_str)
{
	if (new_str)
    {
        // Si la variable tiene un valor y estamos en comillas dobles o sin comillas
        if (cmd->doble || !cmd->simple)
            cmd->full_cmd = str_replace(cmd->full_cmd, name, new_str);
    }
    else
    {
        // Si no tiene valor y no estamos en comillas simples, reemplazamos por ""
        if (!cmd->simple)
            cmd->full_cmd = str_replace(cmd->full_cmd, name, "");
    }
    free(name);
    if (new_str)
        free(new_str);
}


char	*get_name(int i, t_cmd *cmd)
{
	char	*name;
	size_t	len;
	int		start;

	start = i;
	while (ft_isalnum(cmd->full_cmd[i]))
			i++;
	len = (ft_strlen(cmd->full_cmd) - i) - start;
	name = ft_substr(cmd->full_cmd, start, len);
	return (name);
}
char *do_expansion(char *name, t_mini *mini)
{
	int		x;

	x = -1;
	if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
		return(ft_itoa(mini->last_status));
	if (!name)
		return (NULL);
	while (mini->envp[++x])
	{
		if (ft_strncmp(name, mini->envp[x], ft_strlen(name) == 0))
			return (ft_strrchr(mini->envp[x], '=') + 1);
		else
			return (NULL);
	}
	return (NULL);
}
