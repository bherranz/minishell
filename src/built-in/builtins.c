/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:55:03 by codespace         #+#    #+#             */
/*   Updated: 2025/01/06 16:57:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main_builtins(t_cmd *cmd, t_mini *mini)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd, mini));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, mini->envp));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(mini, cmd->args), 0);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(mini, cmd->args), 0);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(mini->envp));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(mini, cmd->args));
	return (1);
}
