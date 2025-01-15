/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:08:12 by codespace         #+#    #+#             */
/*   Updated: 2025/01/15 16:09:55 by codespace        ###   ########.fr       */
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
