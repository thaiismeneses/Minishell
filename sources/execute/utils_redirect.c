/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:56:05 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/25 14:03:32 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*before_redirect(char *value)
{
	char	*before;
	int		i;

	i = 0;
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

char	*after_redirect(char *value)
{
	char	*after;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (value[i] != '<' && value[i] != '>' && value[i] != '\0')
		i++;
	if (value[i] == '\0')
		return (NULL);
	after = malloc(sizeof(char) * ft_strlen(value));
	if (!after)
		return (NULL);
	i++;
	if (value[i++] == '>')
		i++;
	while (value[i] != '\0')
	{
		while (isblank(value[i]))
			i++;
		after[j] = value[i];
		i++;
		j++;
	}
	after[j] = '\0';
	return (after);
}

char	*find_redirect(char *value)
{
	while (*value != '\0')
	{
		if (*value == '<')
			return ("<");
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
