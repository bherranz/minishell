/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 05:02:34 by codespace         #+#    #+#             */
/*   Updated: 2024/09/24 05:14:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(char *msg, int perr, int err)
{
	if (perr)
		perror(msg);
	else
		ft_putendl_fd(msg, 2);
	exit (err);
}
