/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:51:59 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:15:14 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*set_token_list(t_token *data, char *value_cmd, int type)
{
	add_node(&data, type, value_cmd);
	return (data);
}

t_token	*get_last_token(t_token *data)
{
	t_token	*current;

	current = data;
	while (current->next)
		current = current->next;
	return (current);
}

char	*str_join(char *dest, char *src)
{
	char	*result;
	if (!src)
		return (dest);
	if (!dest)
	{
		result = ft_strdup(src);
		return (result);
	}
	result = ft_strjoin(dest, src);
	free(dest);
	return (result);
}

char	*join_cmd(char *dest, char *src, int space)
{
	if (space == 1)
	{
		dest = str_join(dest, src);
		dest = str_join(dest, " ");
	}
	else
		dest = str_join(dest, src);
	return (dest);
}
