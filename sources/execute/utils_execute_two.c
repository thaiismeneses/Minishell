/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:51:56 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/31 13:42:14 by thfranco         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include <stdlib.h>

int is_quote(char c)
{
	return (c == '"' || c == '\'');
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
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			quote_char = str[i];
			inside_quotes = 1;
			i++;
		}
		len = 0;
		int start = i;
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
