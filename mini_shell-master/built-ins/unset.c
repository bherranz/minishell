/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:23 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:13:24 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	is_not_deleted(char *line, char **txt)
{
	int	i;
	int	len;

	i = 0;
	while (txt[i])
	{
		len = ft_strchr(line, '=') - line;
		if (ft_strncmp(txt[i], line, len) == 0 && \
				ft_strlen(txt[i]) == (size_t)len && \
				ft_strncmp(txt[i], "_", 1) != 0)
			return (0);
		i++;
	}
	return (1);
}

static char	**malloc_vars(int count, char **txt, t_mini_shell *ms)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while (ms->envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i - count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (ms->envp[i])
	{
		if (is_not_deleted(ms->envp[i], txt))
		{
			new_envp[j] = ft_strdup(ms->envp[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_strs(ms->envp);
	return (new_envp);
}

void	do_unset(char *txt, t_mini_shell *ms)
{
	char	**var_env;
	int		i;
	int		j;
	int		count;
	int		len;

	i = 1;
	count = 0;
	var_env = ft_split(txt, ' ');
	while (var_env[i])
	{
		j = 0;
		while (ms->envp[j])
		{
			len = ft_strchr(ms->envp[j], '=') - ms->envp[j];
			if (ft_strncmp(var_env[i], ms->envp[j], len) == 0 && \
				ft_strlen(var_env[i]) == (size_t)len && \
				ft_strncmp(var_env[i], "_", 1) != 0)
				count++;
			j++;
		}
		i++;
	}
	ms->envp = malloc_vars(count, var_env, ms);
	free_strs(var_env);
}
