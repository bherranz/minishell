/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:28 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:13:29 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static void	add_vars(char ***new_envp, int len, char **txt)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		if (ft_strchr(txt[i], '='))
		{
			(*new_envp)[len] = ft_strdup(txt[i]);
			len++;
		}
		i++;
	}
	(*new_envp)[len] = NULL;
}

static char	**malloc_vars(int count, char **txt, t_mini_shell *ms)
{
	int		len;
	char	**new_envp;

	len = 0;
	while (ms->envp[len])
		len++;
	new_envp = (char **)malloc(sizeof(char *) * (len + count + 1));
	if (!new_envp)
		return (NULL);
	len = 0;
	while (ms->envp[len])
	{
		new_envp[len] = ft_strdup(ms->envp[len]);
		len++;
	}
	add_vars(&new_envp, len, txt);
	free_strs(ms->envp);
	return (new_envp);
}

static int	biggest_envp(t_mini_shell *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->envp[i])
	{
		if (ft_strcmp(ms->envp[i], ms->envp[j]) > 0)
			j = i;
		i++;
	}
	return (j);
}

static void	print_ordered(t_mini_shell *ms)
{
	int	i;
	int	j;
	int	anterior;
	int	print_index;
	int	max;

	j = 0;
	anterior = -1;
	max = biggest_envp(ms);
	while (ms->envp[j])
	{
		i = 0;
		print_index = max;
		while (ms->envp[i])
		{
			if (ft_strcmp(ms->envp[i], ms->envp[print_index]) < 0 && \
				(anterior == -1 || \
				ft_strcmp(ms->envp[i], ms->envp[anterior]) > 0))
				print_index = i;
			i++;
		}
		printf("declare -x \"%s\"\n", ms->envp[print_index]);
		anterior = print_index;
		j++;
	}
}

void	do_export(char *txt, t_mini_shell *ms)
{
	char	**var_env;
	int		i;
	int		count;

	i = 0;
	count = 0;
	var_env = ft_split(txt, ' ');
	if (!var_env[1])
	{
		print_ordered(ms);
		free_strs(var_env);
		return ;
	}
	while (var_env[i])
	{
		if (ft_strchr(var_env[i], '='))
			count++;
		i++;
	}
	ms->envp = malloc_vars(count, var_env, ms);
	free_strs(var_env);
}
