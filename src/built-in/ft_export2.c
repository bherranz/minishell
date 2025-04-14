/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:08:12 by codespace         #+#    #+#             */
/*   Updated: 2025/02/09 22:50:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_export(char *var, t_mini *mini)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	mini->last_status = 1;
}

int	check_var(char *var, t_mini *mini)
{
	int		i;
	char	**temp;

	i = 0;
	if (var[i] == '=')
		return (error_export(var, mini), 0);
	temp = ft_split(var, '=');
	if ((!ft_isalpha(temp[0][i]) && temp[0][i] != '_') || !temp[0][i])
		return (free_array(temp), error_export(var, mini), 0);
	i++;
	while (temp[0][i])
	{
		if (!ft_isalnum(temp[0][i]) && temp[0][i] != '_')
			return (free_array(temp), error_export(var, mini), 0);
		i++;
	}
	return (free_array(temp), 1);
}

void	print_export(char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) != 0)
		{
			temp = ft_strchr(envp[i], '=');
			write(1, "declare -x ", 11);
			if (temp)
			{
				write(1, envp[i], temp - envp[i] + 1);
				write(1, "\"", 1);
				write(1, temp + 1, ft_strlen(temp + 1));
				write(1, "\"\n", 2);
			}
			else
				printf("%s\n", envp[i]);
		}
		i++;
	}
}
