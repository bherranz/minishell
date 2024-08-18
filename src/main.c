/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bherranz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:46:12 by bherranz          #+#    #+#             */
/*   Updated: 2024/08/18 14:46:13 by bherranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	mini.envp = envp;
	//solo era para compilar
	(void)mini;
	(void)argc;
	(void)argv;
	//pone en el subject Cuando sea interactivo: ctrl-D termina el shell.
	//así que maybe hay que  usar el gnl en vez de while(1)
	while (1)
	{
	}
	return (0);
}
