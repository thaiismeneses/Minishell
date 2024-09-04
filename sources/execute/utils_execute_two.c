/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:51:56 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 17:29:40 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>

int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	skip_whitespace(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int count_words(char *str)
{
	int w;
	int inside_quotes;
	char quote_char;

	w = 0;
	while (*str != '\0')
	{
		while (*str == ' ' || *str == '\t')
			str++;
		quote_char = *str;
		inside_quotes = 1;
		str++;
		if (*str != '\0')
			w++;
		while (*str != '\0' && (inside_quotes || (*str != ' ' && *str != '\t')))
		{
			if (inside_quotes && *str == quote_char)
			{
				inside_quotes = 0;
				str++;
				break;
			}
			str++;
		}
	}
	return w;
}

char	**to_malloc_matriz(char **str, int len)
{
	str = (char **)malloc(sizeof(char*) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

int handle_quotes(char *str, int *i, char *quote_char, int *inside_quotes)
{
    if (str[*i] == '"' || str[*i] == '\'')
    {
        *quote_char = str[*i];
        *inside_quotes = 1;
        (*i)++;
        return 1;
    }
    return 0;
}
int process_word(char *str, int *i, int *inside_quotes, char quote_char)
{
    int len = 0;

    while (str[*i] != '\0' && (*inside_quotes || (str[*i] != ' ' && str[*i] != '\t')))
    {
        if (*inside_quotes && str[*i] == quote_char)
        {
            *inside_quotes = 0;
            (*i)++;
            break;
        }
        (*i)++;
        len++;
    }

    return len;
}

char **new_split(char *str)
{
    int i;
    int j;
    int r;
    int len;
    int cw;
    char **result;
    int inside_quotes;
    char quote_char;

    cw = count_words(str);
    i = 0;
    r = 0;
    inside_quotes = 0;
    quote_char = '\0';
    result = NULL;
    result = to_malloc_matriz(result, cw);
    while (str[i] != '\0')
    {
		i = skip_whitespace(str, i);
        handle_quotes(str, &i, &quote_char, &inside_quotes);
        int start = i;

        // Chama a função process_word
        len = process_word(str, &i, &inside_quotes, quote_char);

        if (len > 0) // Adiciona a palavra apenas se ela tiver comprimento > 0
        {
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
    }
    result[r] = NULL;
    return result;
}
