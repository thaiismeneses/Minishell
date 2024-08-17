/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:06 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 14:10:02 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*create_tree_node(t_type_cmd type, char *value)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (!node)
	{
		perror("Failed to allocate memory for tree node");
		return (NULL);
	}
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	add_node(t_token **data, t_type_cmd type, char *value)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = NULL;
	last_node = NULL;
	if (!data)
		return ;
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->token = type;
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!(*data))
		(*data) = new_node;
	else
	{
		last_node = get_last_token(*data);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}
