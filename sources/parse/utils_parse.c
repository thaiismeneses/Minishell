/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:00:17 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/24 17:55:24 by thfranco         ###   ########.fr       */
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
		unlink(node->redir_info.file);
		free(node->redir_info.file);
		node->redir_info.file = NULL;
	}
	free(node);
	node = NULL;
}

t_redirect_info	init_info(void)
{
	t_redirect_info	redir_info;

	redir_info.fd_in = 0;
	redir_info.fd_out = 1;
	redir_info.heredoc_fd = -1;
	redir_info.command = NULL;
	redir_info.new_cmd = NULL;
	redir_info.file = NULL;
	return (redir_info);
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
	root->redir_info = init_info();
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
