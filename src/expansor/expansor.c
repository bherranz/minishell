/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:40:02 by miparis           #+#    #+#             */
/*   Updated: 2024/10/22 12:53:25 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_var(t_mini *mini, t_cmd *cmd)
{
	int		i;
    char    *str;
    char    *str2;

	i = 0;
    str = NULL;
    str2 = NULL;
	while (cmd->full_cmd[i])
	{
		if (cmd->full_cmd[i] == '\'')
			cmd->simple = !cmd->simple;
		if (cmd->full_cmd[i] == '$' && !cmd->simple)
			handle_expansor(mini, cmd, &str, &str2, i);
		i++;
	}
    replace_var(cmd, str, cmd->e_input, str2);
	printf("Cadena con expansion: %s\n", cmd->full_cmd);
	return (0);
}

void	replace_var(t_cmd *cmd, char *str, char *e_str, char *str2)
{
	if (e_str)
    {
        if (cmd->doble || !cmd->simple)
        {
            free(cmd->full_cmd);
            cmd->full_cmd = ft_strjoin(str, e_str);
            if (str2 != NULL) //ver si tiene que ser str2
                cmd->full_cmd = ft_strjoin(cmd->full_cmd, str2);
        }
    }
}


char	*get_name(int i, char *cmd)
{
	char	*name;
	int		start;
    int     name_len;

	start = i;
    name_len = 0;
	while (cmd[i] && (ft_isalnum(cmd[i]) == 1))
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
void do_expansion(char *name, t_mini *mini, t_cmd *cmd)
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
        	cmd->e_input = (ft_strrchr(mini->envp[x], '=') + 1);
        x++;
	}
}


char *rest_str(int i, char *name, t_cmd cmd)
{
    if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
        return (ft_substr(cmd.full_cmd, (i + ft_strlen(name)), ft_strlen(cmd.full_cmd) - (i + ft_strlen(name))));
    else
        return (ft_substr(cmd.full_cmd, (i + ft_strlen(name) + 1), ft_strlen(cmd.full_cmd) - (i + ft_strlen(name) + 1)));
}

void	handle_expansor(t_mini *mini, t_cmd *cmd, char **str, char **str2, int i)
{
    *str = ft_substr(cmd->full_cmd, 0 , i);  // Usamos *str para modificar el valor del puntero
	if (cmd->full_cmd[i + 1] == '?')
	{
		cmd->ex_var = "$?";  // Usamos *name
		*str2 = rest_str(i, cmd->ex_var, *cmd);  // Usamos los valores desreferenciados
		do_expansion(cmd->ex_var, mini, cmd);
	}
	else if (cmd->full_cmd[i + 1] != '\0')
	{
		cmd->ex_var = get_name(i + 1, cmd->full_cmd);
		*str2 = rest_str(i, cmd->ex_var, *cmd);
		do_expansion(cmd->ex_var, mini, cmd);
	}
}