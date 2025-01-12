/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:13 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 13:10:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (!path)
	{
		perror("pwd");
		free(path);
		mini->last_status = 1;
		return ;
	}
	mini->last_status = 0;
	printf("%s\n", path);
	free(path);
	return ;
}
