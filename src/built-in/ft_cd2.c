/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bherranz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:24:40 by bherranz          #+#    #+#             */
/*   Updated: 2025/01/16 17:24:47 by bherranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	cd_hyphen(char **envp, t_mini *mini)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD", envp);
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
