/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:58:59 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:16:29 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree_node	*init_tree()
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
	t_token *temp;

	temp = get_last_token(data);
	while (temp)
	{
		if (temp->token == PIPE)
			return (temp);
		temp = temp->prev;
	}
	return (NULL);
}

t_token *node_right(t_token *data, t_token *node)
{
	t_token	*temp;
	t_token *right;

	right = NULL;
	temp = data;
	while (temp && temp != node)
		temp = temp->next;
	temp = temp->next;
	while (temp)
	{
		add_node(&right, temp->token, temp->value);
		temp = temp->next;
	}
	return (right);
}

t_token *node_left(t_token *data, t_token *node)
{
	t_token	*temp;
	t_token *left;

	left = NULL;
	temp = data;
	while (temp && temp != node)
	{
		add_node(&left, temp->token, temp->value);
		temp = temp->next;
	}
	return (left);
}


int	build_branch(t_tree_node *root, t_token *data, t_token *node)
{
	t_token	*left;
	t_token *right;

	if (!root | !data | !node)
		return (0);
	right = node_right(data, node);
	left = node_left(data, node);
	//free_list_two(data);
	root->type = node->token;
	root->value = ft_strdup(node->value);
	root->left = parse(left);
	root->right = parse(right);
	return (1);
}

void	verify_priority(t_tree_node *root, t_token *data)
{
	t_token *pipe;

	pipe = search_pipe(data);
	if (!pipe)
	{
		root->value = ft_strdup(data->value);
		root->type = data->token;
	}
	else if (!build_branch(root, data, pipe))
		return ;
}

t_tree_node	*parse(t_token *data)
{
	t_tree_node	*root;

	root = init_tree();
	if (!root)
		return (NULL);
	verify_priority(root, data);
	return (root);
}
