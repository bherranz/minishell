/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:03 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:13:04 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	skip_quotes(char *txt, char com)
{
	int	i;

	i = 1;
	while (txt[i] && txt[i] != com)
		i++;
	return (i);
}

char	*get_literal(char *txt, int *i)
{
	char	comilla;
	char	*literal;
	char	*aux;
	int		j;

	j = 0;
	comilla = txt[*i];
	(*i)++;
	while (txt[*i + j] != comilla)
		j++;
	literal = gnl_substr(txt + (*i), 0, j);
	*i += j + 1;
	j = 0;
	while (txt[*i + j] && !(txt[*i + j] == ' ' || \
	(txt[*i + j] <= 13 && txt[*i + j] >= 9)))
		j++;
	aux = gnl_substr(txt, *i, j);
	literal = gnl_strjoin(literal, aux);
	if (aux)
		free(aux);
	return (literal);
}
