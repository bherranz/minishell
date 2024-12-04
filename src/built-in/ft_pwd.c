/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:39:13 by codespace         #+#    #+#             */
/*   Updated: 2024/12/03 02:47:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (!path)
	{
		perror("pwd");
		free(path);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
