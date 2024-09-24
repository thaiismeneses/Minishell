/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:00:17 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/24 10:19:52 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree_node(t_tree_node *node)
{
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	if (node->redir_info.command)
	{
		free(node->redir_info.command);
		node->redir_info.command = NULL;
	}
	if (node->redir_info.new_cmd)
	{
		free(node->redir_info.new_cmd);
		node->redir_info.new_cmd = NULL;
	}
	if (node->redir_info.file)
	{
		free(node->redir_info.file);
		node->redir_info.file = NULL;
	}
}

t_tree_node	*init_tree(void)
{
	t_tree_node	*root;

	root = malloc(sizeof(t_tree_node));
	if (!root)
		return (NULL);
	root->left = NULL;
	root->right = NULL;
	root->value = NULL;
	root->redir_info.fd_in = 0;
	root->redir_info.fd_out = 1;
	root->redir_info.heredoc_fd = -1;
	root->redir_info.command = NULL;
	root->redir_info.new_cmd = NULL;
	root->redir_info.file = NULL;
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
