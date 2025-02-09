/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:22:02 by miparis           #+#    #+#             */
/*   Updated: 2025/02/09 23:38:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*rest_str(int i, char *name, t_cmd cmd)
{
	int		n_l;
	int		f_l;

	n_l = ft_strlen(name);
	f_l = ft_strlen(cmd.full_cmd);
	if (ft_strncmp(name, "$?", n_l) == 0)
		return (ft_substr(cmd.full_cmd, (i + n_l), f_l - (i + n_l)));
	else
		return (ft_substr(cmd.full_cmd, (i + n_l + 1), f_l - (i + n_l + 1)));
}
