/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:13:06 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:16:55 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redirect_info	init_redirect_info(void)
{
	t_redirect_info	redir_info;

	redir_info.command = NULL;
	redir_info.fd_in = 0;
	redir_info.fd_out = 0;
	redir_info.heredoc_fd = -1;
	redir_info.new_cmd = NULL;
	redir_info.file = NULL;
	return (redir_info);
}

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
	node->redir_info = init_redirect_info();
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

void	free_list_two(t_token *data)
{
	t_token	*current;
	t_token	*temp;

	if (!data)
		return ;
	current = data;
	while (current)
	{
		temp = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = temp;
	}
	data = NULL;
}
