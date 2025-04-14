/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:55:03 by codespace         #+#    #+#             */
/*   Updated: 2025/01/15 12:46:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	main_builtins(t_cmd *cmd, t_mini *mini)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd, mini);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, mini->envp, mini);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(mini);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(mini, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(mini, cmd->args);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(mini->envp, cmd, mini);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(mini, cmd->args);
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
