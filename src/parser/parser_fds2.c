/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fds2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:15:49 by codespace         #+#    #+#             */
/*   Updated: 2025/01/19 13:16:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (4);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (3);
	return (0);
}

void	print_list(t_io_file *list)
{
	while (list)
	{
		printf("%s ", list->name);
		list = list->next;
	}
	printf("\n");
}

void	list_addback(t_io_file *node, t_io_file **list)
{
	t_io_file	*tmp;

	if (!list || !node)
		return ;
	if (!(*list))
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
