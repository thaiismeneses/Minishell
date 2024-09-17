/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:46:57 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:47:13 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_whitespace(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

char	**to_malloc_matrix(char **str, int len)
{
	str = (char **)malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

int	handle_quotes(char *str, int *i, char *quote_char, int *inside_quotes)
{
	if (str[*i] == '"' || str[*i] == '\'')
	{
		*quote_char = str[*i];
		*inside_quotes = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

int	process_word(char *str, int *i, int *inside_quotes, char quote_char)
{
	int	len;

	len = 0;
	while (str[*i] != '\0' && (*inside_quotes || (str[*i] != ' '
				&& str[*i] != '\t')))
	{
		if (*inside_quotes && str[*i] == quote_char)
		{
			*inside_quotes = 0;
			(*i)++;
			break ;
		}
		(*i)++;
		len++;
	}
	return (len);
}
