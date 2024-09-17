/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:00:17 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/17 12:04:46 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*handle_token(t_token **data, t_tree_node *current,
		t_tree_node *node)
{
	t_tree_node	*arg_node;
	char		*value;

	if ((*data)->token == REDIRECT_IN || (*data)->token == REDIRECT_OUT
		|| (*data)->token == HEREDOC || (*data)->token == APPEND)
	{
		free_tree(node);
		node = create_redirect_node(data);
	}
	else
	{
		value = ft_strdup((*data)->value);
		arg_node = create_tree_node((*data)->token, value);
		free(value);
		current->left = arg_node;
		current = arg_node;
	}
	*data = (*data)->prev;
	return (node);
}
