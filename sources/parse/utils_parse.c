/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:00:17 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/19 09:33:25 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*init_tree(void)
{
	t_tree_node	*root;

	root = malloc(sizeof(t_tree_node));
	if (!root)
		return (NULL);
	root->left = NULL;
	root->right = NULL;
	root->value = NULL;
	return (root);
}

t_token	*search_pipe(t_token *data)
{
	t_token	*temp;

	temp = get_last_token(data);
	while (temp)
	{
		if (temp->token == PIPE)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}
