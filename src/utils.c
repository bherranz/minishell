/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 05:02:34 by codespace         #+#    #+#             */
/*   Updated: 2024/11/19 10:52:26 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(char *msg, char *var, int perr, int err)
{
	if (perr)
		perror(msg);
	else
		ft_putendl_fd(msg, var, 2);
	(void)err;
}



