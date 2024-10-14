/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:40:02 by miparis           #+#    #+#             */
/*   Updated: 2024/10/14 10:08:59 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_var(t_mini *mini, t_cmd *cmd)
{
	int		i;
	char	*new_str;
	char	*name;

	i = 0;
	cmd->simple = false;
	cmd->doble = false;
	cmd->key = false;
	new_str = NULL;
	while (cmd->full_cmd[i])
	{
		if (cmd->full_cmd[i] == '\'')
			cmd->simple = !cmd->simple;
		if (cmd->full_cmd[i] == '$' && !cmd->simple)
		{
			if (cmd->full_cmd[i + 1] == '?')
			{
				printf("Case '$?' : %d\n", cmd->full_cmd[i]);
				name = "$?";
				new_str = do_expansion(name, mini);
				printf("After expansion: %s\n", new_str);
			}
			else if (cmd->full_cmd[i + 1] != '\0')
			{
				name = get_name(i + 1, cmd);
				new_str = do_expansion(name, mini);
				printf("After expansion: %s\n", new_str);
			}
		}
		i++;
	}
	replace_var(cmd, name, new_str);
	printf("Cadena con expansion: %s\n", cmd->full_cmd);
	return (0);
}

void	replace_var(t_cmd *cmd, char *name, char *new_str)
{
	if (new_str)
    {
        // Si la variable tiene un valor y estamos en comillas dobles o sin comillas
        if (cmd->doble || !cmd->simple)
            cmd->full_cmd = str_replace(cmd->full_cmd, name, new_str);
    }
    else
    {
        // Si no tiene valor y no estamos en comillas simples, reemplazamos por ""
        if (!cmd->simple)
            cmd->full_cmd = str_replace(cmd->full_cmd, name, "");
    }
    free(name);
    if (new_str)
        free(new_str);
}


char	*get_name(int i, t_cmd *cmd)
{
	char	*name;
	size_t	len;
	int		start;

	printf("Get Name\n");
	start = i;
	while (ft_isalnum(cmd->full_cmd[i]))
			i++;
	len = i - start;
	name = ft_substr(cmd->full_cmd, start, len);
	printf("Name found for var. expansion: %s\n", name);
	if (!name)
	{
		printf("Name not found\n");
		return (NULL);
	}
	return (name);
}
char *do_expansion(char *name, t_mini *mini)
{
	int		x;

	x = -1;
	if (ft_strncmp(name, "$?", ft_strlen(name)) == 0)
		return(ft_itoa(mini->last_status));
	if (!name)
		return (NULL);
	while (mini->envp[++x])
	{
		if (ft_strncmp(name, mini->envp[x], ft_strlen(name) == 0))
			return (ft_strrchr(mini->envp[x], '=') + 1);
		else
			return (NULL);
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Suponiendo que estas funciones están definidas en otro lugar
char *ft_substr(const char *s, unsigned int start, size_t len);
char *do_expansion(const char *name, void *mini);

typedef struct s_cmd {
    char *full_cmd;
} t_cmd;

char *get_name(t_cmd *cmd, int i)
{
    int start;
    int len;
    char *name;

    start = i;
    while (isalnum(cmd->full_cmd[i]))
        i++;
    len = i - start; // Corregir el cálculo de la longitud
    name = ft_substr(cmd->full_cmd, start, len);
    if (!name)
    {
        printf("Error: Name not found for var. expansion\n");
        return NULL;
    }
    printf("Name found for var. expansion: %s\n", name);
    return name;
}

void process_command(t_cmd *cmd, void *mini)
{
    int i = 0;
    char *name;
    char *new_str;

    while (cmd->full_cmd[i] != '\0')
    {
        if (cmd->full_cmd[i] == '$')
        {
            if (cmd->full_cmd[i + 1] == '?')
            {
                printf("Case '$?' : %d\n", cmd->full_cmd[i]);
                name = "$?";
                new_str = do_expansion(name, mini);
                printf("After expansion: %s\n", new_str);
            }
            else if (cmd->full_cmd[i + 1] != '\0')
            {
                name = get_name(cmd, i + 1);
                if (name) // Verificar si name no es NULL antes de usarlo
                {
                    new_str = do_expansion(name, mini);
                    printf("After expansion: %s\n", new_str);
                    free(name); // Liberar memoria si es necesario
                }
            }
        }
        i++;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Suponiendo que estas funciones están definidas en otro lugar
char *ft_substr(const char *s, unsigned int start, size_t len);
char *do_expansion(const char *name, void *mini);

typedef struct s_cmd {
    char *full_cmd;
} t_cmd;

char *get_name(t_cmd *cmd, int i)
{
    int start;
    int len;
    char *name;

    start = i;
    while (isalnum(cmd->full_cmd[i]))
        i++;
    len = i - start; // Corregir el cálculo de la longitud
    name = ft_substr(cmd->full_cmd, start, len);
    if (!name)
    {
        printf("Error: Name not found for var. expansion\n");
        return NULL;
    }
    printf("Name found for var. expansion: %s\n", name);
    return name;
}

char *do_expansion(const char *name, void *mini)
{
    // Implementación de ejemplo para la expansión de variables
    // Aquí se debería implementar la lógica real de expansión
    if (name == NULL)
    {
        printf("Error: Name is NULL in do_expansion\n");
        return NULL;
    }

    // Ejemplo de expansión: simplemente devuelve el nombre con un prefijo "expanded_"
    char *expanded_name = malloc(strlen(name) + 10); // Asignar memoria para el nuevo nombre
    if (!expanded_name)
    {
        printf("Error: Memory allocation failed in do_expansion\n");
        return NULL;
    }
    sprintf(expanded_name, "expanded_%s", name);
    return expanded_name;
}

void process_command(t_cmd *cmd, void *mini)
{
    int i = 0;
    char *name;
    char *new_str;

    while (cmd->full_cmd[i] != '\0')
    {
        if (cmd->full_cmd[i] == '$')
        {
            if (cmd->full_cmd[i + 1] == '?')
            {
                printf("Case '$?' : %d\n", cmd->full_cmd[i]);
                name = "$?";
                new_str = do_expansion(name, mini);
                if (new_str) // Verificar si new_str no es NULL antes de imprimir
                {
                    printf("After expansion: %s\n", new_str);
                    free(new_str); // Liberar memoria si es necesario
                }
            }
            else if (cmd->full_cmd[i + 1] != '\0')
            {
                name = get_name(cmd, i + 1);
                if (name) // Verificar si name no es NULL antes de usarlo
                {
                    new_str = do_expansion(name, mini);
                    if (new_str) // Verificar si new_str no es NULL antes de imprimir
                    {
                        printf("After expansion: %s\n", new_str);
                        free(new_str); // Liberar memoria si es necesario
                    }
                    free(name); // Liberar memoria si es necesario
                }
            }
        }
        i++;
    }
}

int main()
{
    // Ejemplo de uso
    t_cmd cmd = { .full_cmd = "echo $USER" };
    void *mini = NULL; // Suponiendo que mini se inicializa en otro lugar

    process_command(&cmd, mini);

    return 0;
}

int main()
{
    // Ejemplo de uso
    t_cmd cmd = { .full_cmd = "echo $USER" };
    void *mini = NULL; // Suponiendo que mini se inicializa en otro lugar

    process_command(&cmd, mini);

    return 0;
}*/