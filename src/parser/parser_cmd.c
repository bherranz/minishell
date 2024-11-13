/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:42:28 by codespace         #+#    #+#             */
/*   Updated: 2024/11/13 11:32:00 by miparis          ###   ########.fr       */
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
		if (str[end] == '\'')
			cmd->simple = !cmd->simple;
		else if (str[end] == '"')
			cmd->doble = !cmd->doble;
		else if (!cmd->simple && !cmd->doble && (str[end] == '<' || str[end] == '>'))
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
		return NULL;
	token = ft_substr(str, start, end - start);
	return (token);
}


void	process_quotes(char c, t_cmd *cmd)
{
	if (c == '\'')
		cmd->simple = !cmd->simple;
	else if (c == '"')
		cmd->doble = !cmd->doble;
}

void process_args(char *str, int *i, t_cmd *cmd)
{
	//para malloc funciona okay
    while (ft_isspace(str[*i]))
        (*i)++;
   // process_quotes(str[*i], cmd);
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
	//printf("--> SKIP NOT ARGS2\n");
     while (ft_isspace(str[*i]))
        (*i)++;
    //process_quotes(str[*i], cmd);
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

int count_arguments(char *str, t_cmd *cmd)
{
    int count = 0;
    char *token;
    int i = 0;

    while (str[i])
    {
		process_args(str, &i, cmd);
		printf("str: %s\n", &str[i]);
        if (str[i])
        {
            token = get_token(&str[i], cmd);
            if (token)
            {
                count++;
                i += ft_strlen(token) - 1;
                free(token);
            }
			i++;
        }
    }
    return count;
}

int main_cmd(char *str, t_cmd *cmd)
{
	int i;
	char *token;
	int space;
	int x;

	i = 0;
	space = 0;
	x = 0;
	cmd->simple = false;
	cmd->doble = false;
	space = count_arguments(str, cmd);
	printf(" ------> Spaces = %i\n", space);
	cmd->args = malloc(sizeof(char *) * space);
	printf(" ------> Malloqueado = %i\n", space);
	parse_redir(str, cmd);
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
			if (token)
			{
				cmd->args[x] = token;
				printf("ARG[%i] = %s\n", x, cmd->args[x]);
				x++;
				i += ft_strlen(token) - 1;
			}
			i++;
		}
	}
	return (0);
}

int	parse_cmds(t_mini *mini)
{
	int i;

	i = 0;
	while (i <= mini->pipes)
	{
		printf("command: %s\n", mini->cmd[i]->full_cmd);
		if (main_cmd(mini->cmd[i]->full_cmd, mini->cmd[i]) != 0)
		 	return (-1);
		i++;
	}
	return (0);
}

