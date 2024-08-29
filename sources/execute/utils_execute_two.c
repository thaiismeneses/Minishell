/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:51:56 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/29 16:35:11 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
int count_words(char *str)
{
    int i = 0;
    int w = 0;
    int inside_quotes = 0;
    char quote_char = '\0';

    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;

        if (str[i] == '"' || str[i] == '\'')
        {
            quote_char = str[i];
            inside_quotes = 1;
            i++;
        }

        if (str[i] != '\0')
            w++;

        while (str[i] != '\0' && (inside_quotes || (str[i] != ' ' && str[i] != '\t')))
        {
            if (inside_quotes && str[i] == quote_char)
            {
                inside_quotes = 0;
                i++;
                break;
            }
            i++;
        }
    }
    return w;
}

char **new_split(char *str)
{
    int i = 0;
    int j;
    int r = 0;
    int len;
    int cw = count_words(str);
    char **result;
    int inside_quotes = 0;
    char quote_char = '\0';

    result = (char **)malloc(sizeof(char *) * (cw + 1));
    if (!result)
        return (NULL);

    while (str[i] != '\0')
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;

        if (str[i] == '"' || str[i] == '\'')
        {
            quote_char = str[i];
            inside_quotes = 1;
            i++;
        }

        len = 0;
        int start = i; // Armazena o início da palavra

        while (str[i] != '\0' && (inside_quotes || (str[i] != ' ' && str[i] != '\t')))
        {
            if (inside_quotes && str[i] == quote_char)
            {
                inside_quotes = 0;
                i++;
                break;
            }
            i++;
            len++;
        }

        result[r] = (char *)malloc(sizeof(char) * (len + 1));
        if (!result[r])
            return (NULL);

        j = 0;
        while (j < len)
        {
            result[r][j] = str[start + j];
            j++;
        }
        result[r][j] = '\0'; // Adiciona o terminador nulo ao final da string

        r++;
    }
    result[r] = NULL;
    return result;
}
