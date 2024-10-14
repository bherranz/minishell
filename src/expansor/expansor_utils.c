/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:22:02 by miparis           #+#    #+#             */
/*   Updated: 2024/10/14 09:38:48 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *replace_once(const char *str, const char *old, const char *new)
{
    char    *result;
    char    *found;
    int     new_len;
    int     old_len;
    int     len_before;

    new_len = ft_strlen(new);
    old_len = ft_strlen(old);
    // Buscamos la primera aparición de 'old' en 'str'
    found = ft_strnstr(str, old, old_len);
    if (!found)
        return ((char *)str); // Si no encontramos la variable, devolvemos una copia del string original

    // Calculamos el tamaño de la nueva cadena
    len_before = found - str;
    result = malloc(len_before + new_len + ft_strlen(found + old_len) + 1);
    if (!result)
        return NULL;

    // Copiamos la parte antes de la ocurrencia de 'old'
    ft_strlcpy(result, str, len_before);
    result[len_before] = '\0';

    // Añadimos 'new' en lugar de 'old'
    ft_strlcat(result, new, ft_strlen(new));

    // Añadimos el resto de la cadena después de 'old'
    ft_strlcat(result, found + old_len, ft_strlen(found) - old_len);

    return result;
}

char *str_replace(char *str, const char *old, const char *new)
{
    char *new_str;
    char *temp;

    new_str = str;
    while ((temp = replace_once(new_str, old, new)) != NULL)
    {
        if (new_str != str) // Si no es la cadena original, liberamos la anterior
            free(new_str);
        new_str = temp;

        // Salimos si no se hace ningún reemplazo más
        if (ft_strnstr(old, new_str,ft_strlen(new_str)) == NULL)
            break;
    }
    return new_str;
}
