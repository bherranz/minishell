/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:20:33 by miparis           #+#    #+#             */
/*   Updated: 2024/10/15 12:37:23 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **array_split)
{
	int	i;

	if (!array_split)
		return ;
	i = 0;
	while (array_split[i])
	{
		free(array_split[i]);
		i++;
	}
	free(array_split);
}
