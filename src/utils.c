/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 05:02:34 by codespace         #+#    #+#             */
/*   Updated: 2024/09/26 09:10:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(char *msg, int perr, int err)
{
	if (perr)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	(void)err;
}



