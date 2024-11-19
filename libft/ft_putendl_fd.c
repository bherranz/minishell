/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:02 by bherranz          #+#    #+#             */
/*   Updated: 2024/11/19 10:56:30 by miparis          ###   ########.fr       */
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
		while(*var != '\0')
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