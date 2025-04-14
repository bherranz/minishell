/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:02 by bherranz          #+#    #+#             */
/*   Updated: 2025/01/18 17:00:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, char *var, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
	if (*var)
	{
		while (*var != '\0')
		{
			write(fd, var, 1);
			var++;
		}
	}
	write(fd, "\n", 1);
}

/*int main(void)
{
	char str[] = "hello";

	ft_putendl_fd(str, 1);
	return (0);
}*/