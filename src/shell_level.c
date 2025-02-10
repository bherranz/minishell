/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 00:12:31 by codespace         #+#    #+#             */
/*   Updated: 2025/02/10 17:32:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_shlvl(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strdup("SHLVL=0");
			return ;
		}
		i++;
	}
}

int	find_level(int level, int start)
{
	if (level <= 0)
		return (0);
	else if (level > 999)
	{
		write(2, "MINICONCHAA: warning: shell level (", 35);
		ft_putnbr_fd(level, 2);
		write(2, ") too high, resetting to 1\n", 27);
		return (1);
	}
	if (start)
		return (level + 1);
	else
		return (level - 1);
}

char	*shell_level(char *envp, int start)
{
	char	*new;
	char	**chop;
	int		level;
	char	*aux;
	int		i;

	chop = ft_split(envp, '=');
	if (!chop || !chop[0] || !chop[1] || chop[2])
		return (free_array(chop), ft_strdup("SHLVL=0"));
	i = 0;
	while (chop[1][i])
	{
		if (!ft_isdigit(chop[1][i]) && !(i == 0 && chop[1][i] == '-'))
			return (free_array(chop), ft_strdup("SHLVL=1"));
		i++;
	}
	level = ft_atoi(chop[1]);
	level = find_level(level, start);
	aux = ft_itoa(level);
	new = ft_strjoin("SHLVL=", aux);
	return (free_array(chop), free(aux), new);
}

void	env_print_shlvl(char *shlvl)
{
	char	*new;

	new = shell_level(shlvl, 0);
	printf("%s\n", new);
	free(new);
}
