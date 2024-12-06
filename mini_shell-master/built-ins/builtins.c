/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:45 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 14:55:54 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	do_builtins(char *txt, t_mini_shell *ms)
{
	char	**str;
	char	*aux;

	aux = expand_variables(txt, ms);
	str = ft_split(aux, ' ');
	if (!str[0] || ft_strchr(aux, '|'))
		return (free_strs(str), -1);
	if (!(ft_strcmp(str[0], "cd")))
		return (free_strs(str), do_cd(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "unset")))
		return (free_strs(str), do_unset(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "exit")))
		return (free_strs(str), do_exit(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "export")) && str[1])
		return (free_strs(str), do_export(txt, ms), free(aux), 0);
	return (free_strs(str), -1);
}

int	exec_builtin(char *txt, t_mini_shell *ms)
{
	char	**str;

	str = ft_split(txt, ' ');
	if (!(ft_strcmp(str[0], "cd")))
		return (free_strs(str), do_cd(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "unset")))
		return (free_strs(str), do_unset(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "exit")))
		return (free_strs(str), do_exit(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "pwd")))
		return (free_strs(str), do_pwd(), 0);
	else if (!(ft_strcmp(str[0], "env")))
		return (free_strs(str), do_envp(ms), 0);
	else if (!(ft_strcmp(str[0], "export")))
		return (free_strs(str), do_export(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "echo")))
		return (free_strs(str), do_echo(txt, ms), 0);
	return (free_strs(str), -1);
}
