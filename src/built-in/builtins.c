/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:55:03 by codespace         #+#    #+#             */
/*   Updated: 2025/01/10 13:46:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main_builtins(t_cmd *cmd, t_mini *mini)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd, mini));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, mini->envp, mini));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(mini));
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(mini, cmd->args), 0);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(mini, cmd->args), 0);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(mini->envp, cmd, mini));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(mini, cmd->args));
	return (1);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
