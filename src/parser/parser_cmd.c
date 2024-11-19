/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/19 11:30:13 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_token(char *str, t_cmd *cmd)
{
	int		start;
	int		end;
	char	*token;

	start = 0;
	while (ft_isspace(str[start]))  // saltar espacios iniciales
		start++;
	end = start;
	while (str[end] && (!ft_isspace(str[end]) || cmd->simple || cmd->doble))
	{
		process_quotes(str[end], cmd);
		/*if (str[end] == '\'')
			cmd->simple = !cmd->simple;
		else if (str[end] == '"')
			cmd->doble = !cmd->doble;*/
		//la siguiente era un else if ante
		if (!cmd->simple && !cmd->doble && (str[end] == '<' || str[end] == '>'))
		{
			if (end == start) // Si el redireccionamiento está al principio
			{
				if (str[end + 1] == str[end]) // Manejar << o >>
					end++;
				end++;
			}
			break;
		}
		end++;
	}
	if (end == start)
		return (NULL);
	token = ft_substr(str, start, end - start);
	return (token);
}

void process_args(char *str, int *i, t_cmd *cmd)
{
    while (ft_isspace(str[*i]))
        (*i)++;
    while ((str[*i] == '<' || str[*i] == '>') || (cmd->simple || cmd->doble))
    {
        if (str[*i + 1] == str[*i])
            (*i) += 2;
        else
            (*i)++;
        while (ft_isspace(str[*i]))
            (*i)++;
        while (str[*i] && (!ft_isspace(str[*i]) || cmd->simple || cmd->doble) && str[*i] != '<' && str[*i] != '>')
        {
            process_quotes(str[*i], cmd);
            (*i)++;
        }
        while (ft_isspace(str[*i]))
            (*i)++;
    }
}

void skip_not_args(char *str, int *i, t_cmd *cmd)
{
	cmd->simple = false;
	cmd->doble = false;
     while (ft_isspace(str[*i]))
        (*i)++;
    while ((str[*i] == '<' || str[*i] == '>') || (cmd->simple || cmd->doble))
    {
        if (str[*i + 1] == str[*i])
            (*i) += 2;
        else
            (*i)++;
		if (!str[*i])
			break;
        while (ft_isspace(str[*i]))
            (*i)++;
        while (str[*i] && (!ft_isspace(str[*i]) || cmd->simple || cmd->doble) && str[*i] != '<' && str[*i] != '>')
        {
            process_quotes(str[*i], cmd);
            (*i)++;
        }
        while (ft_isspace(str[*i]))
            (*i)++;
    }
}

int count_arguments(char *str, t_cmd *cmd)
{
	int		count;
	char	*token;
	int		i;
	char	*clean;

	count = 0;
	i = 0;
    while (str[i])
    {
		process_args(str, &i, cmd);
        if (str[i])
        {
			token = get_token(&str[i], cmd);
			if (!token)
				break;
			clean = clear_token(token, cmd, ft_strlen(token));
            if (clean)
            {
                count++;
                i += ft_strlen(token) - 1;
                free(token);
				free(clean);
            }
			i++;
        }
    }
    return (count);
}

int main_cmd(char *str, t_cmd *cmd)
{
	int		i;
	char	*token;
	int		space;
	int		x;
	char	*clean;

	i = 0;
	space = 0;
	x = 0;
	cmd->simple = false;
	cmd->doble = false;
	space = count_arguments(str, cmd);
	printf(" ------> Spaces = %i\n", space);
	cmd->args = malloc(sizeof(char *) * space);
	printf(" ------> Malloqueado = %i\n", space);
	if (parse_redir(str, cmd))
		return (-1); //liberar cmd->args aca
	printf("Infiles: ");
	print_list(cmd->infile);
	printf("Outfiles: ");
	print_list(cmd->outfile);
	while (str && str[i])
	{
		skip_not_args(str, &i, cmd);
		if (str[i])
		{
			token = get_token(&str[i], cmd);
			if (!token || !*token)
				break;
			clean = clear_token(token, cmd, ft_strlen(token));
			if (clean)
			{
				cmd->args[x] = clean;
				printf("ARG[%i] = %s\n", x, cmd->args[x]);
				x++;
				i += ft_strlen(token) - 1;
				free(clean);
				free(token);
			}
			i++;
		}
	}
	return (0);
}


