/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:56:05 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/27 15:13:48 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*before_redirect(char *value)
{
	char	*before;
	int		i;

	i = 0;
	if (value[0] == '<' || value[0] == '>')
	{
		before = NULL;
		return (before);
	}
	before = malloc(sizeof(char) * ft_strlen(value));
	if (!before)
		return (NULL);
	while (value[i] != '<' && value[i] != '>' && value[i] != '\0')
	{
		before[i] = value[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

int	find_index(char *value)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != '<' && value[i] != '>')
		i++;
	if (value[i] == '\0')
		return (-1);
	if (value[i++] == '>' && value[i] == '>')
		i++;
	return (i);
}

char	*after_redirect(char *value, int *i)
{
	char	*after;
	int		j;
	int size;
	int	init;

	init = *i;
	size = init;
	j = 0;
	while (value[size] != '\0' && isblank(value[size]))
		size++;
	init = size;
	while (value[size] != '\0' && !isblank(value[size]))
		size++;
	after = malloc(sizeof(char) * (size - init + 1));
	if (!after)
		return (NULL);
	while (value[init] != '\0' && !isblank(value[init]))
	{
		after[j++] = value[init++];
	}
	after[j++] = '\0';
	*i = size;
	return (after);
}

char	*find_redirect(char *value)
{
	while (*value != '\0')
	{
		if (*value == '<')
		{
			if (*(value + 1) == '<')
				return ("<<");
			return ("<");
		}
		if (*value == '>')
		{
			if (*(value + 1) == '>')
				return (">>");
			return (">");
		}
		value++;
	}
	return (NULL);
}
