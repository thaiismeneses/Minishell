/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:40:43 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/23 13:29:53 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_redirect(char *value)
{
	while (*value != '\0')
	{
		if (*value == '<') // redirecionamento de entrada
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

void	handle_redirect(t_tree_node *node)
{
	char **value;
	char	*redirect;
	int i;

	i = 0;
	redirect = find_redirect(node->value);
	printf("REDIRECT: %s\n", redirect);
	value = ft_split(node->value, ' ');
	while (value[i])
	{
		printf("VALUE SPLIT: %s\n", value[i]);
		i++;
	}

}

