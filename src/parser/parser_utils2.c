/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:24:36 by codespace         #+#    #+#             */
/*   Updated: 2025/01/18 15:13:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_mini(t_mini *mini)
{
	mini->stdin = 0;
	mini->stdout = 1;
	mini->here_doc = 0;
	mini->cmds = NULL;
	mini->pipes_n = 0;
	mini->cmd = NULL;
	mini->pipes = NULL;
	mini->input = NULL;
}
