/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-g <egomez-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:38 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/02/01 14:34:57 by egomez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

static int	check_nl(char *txt)
{
	int	i;

	i = 0;
	if (txt[i] != '-')
		return (1);
	i++;
	while (txt[i])
	{
		if (txt[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	skip_word(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] != ' ' && !(txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

static void	print_echo(char *txt, t_mini_shell *ms)
{
	int	i;
	int	j;

	i = -1;
	while (txt[i++])
	{
		j = 0;
		skip_spaces(txt + i, &j);
		if (!txt[i + j] || (txt[i + j] == ' ' || \
		(txt[i + j] <= 13 && txt[i + j] >= 9)))
			break ;
		if ((txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9)))
		{
			printf("%c", txt[i]);
			skip_spaces(txt, &i);
			i--;
		}
		else if (txt[i] == '$' && txt[i + 1] && txt[i + 1] == '?')
		{
			printf("%d", WEXITSTATUS(ms->status));
			i += 1;
		}
		else
			printf("%c", txt[i]);
	}
}

static void	skip_no_print(char *txt, int *i, int nl)
{
	skip_spaces(txt, i);
	*i += 4;
	skip_spaces(txt, i);
	while (nl > 0)
	{
		skip_word(txt, i);
		skip_spaces(txt, i);
		nl--;
	}
}

void	do_echo(char *txt, t_mini_shell *ms)
{
	int		i;
	int		nl;
	char	**str;

	str = ft_split(txt, ' ');
	if (!str)
		return ;
	i = 1;
	nl = 0;
	while (str[i] && !check_nl(str[i]))
	{
		i++;
		nl++;
	}
	i = 0;
	skip_no_print(txt, &i, nl);
	print_echo(txt + i, ms);
	if (nl == 0)
		printf("\n");
	free_strs(str);
}
