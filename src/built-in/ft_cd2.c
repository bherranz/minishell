/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:24:40 by bherranz          #+#    #+#             */
/*   Updated: 2025/02/09 21:40:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_hyphen(char **envp, t_mini *mini)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD", envp);
	if (!oldpwd || !*oldpwd)
	{
		write(2, "MINICHONCHAA: cd: OLDPWD not set\n", 33);
		mini->last_status = 1;
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		write(2, "MINICHONCHAA: cd: ", 18);
		write(2, oldpwd, ft_strlen(oldpwd));
		write(2, ": Cannot open that file or directory\n", 38);
		mini->last_status = 1;
		return (1);
	}
	printf("%s\n", oldpwd);
	return (0);
}
