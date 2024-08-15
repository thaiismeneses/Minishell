/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:58:59 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/12 11:14:41 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree_node	*create_redirect_node(t_token **data)
{
	char		*value;
	t_tree_node	*arg_node;

	value = join_cmd(NULL, (*data)->prev->value, 1);
	value = join_cmd(value, (*data)->value, 1);
	value = join_cmd(value, (*data)->next->value, 0);
	arg_node = create_tree_node(COMMAND_SUBSTITUTION, value);
	free(value);
	return (arg_node);
}

t_tree_node	*parse_command(t_token **data)
{
	t_tree_node	*node;
	t_tree_node	*current;
	t_tree_node	*arg_node;

	if (*data == NULL)
		return (NULL);
	node = create_tree_node((*data)->token, (*data)->value);
	*data = (*data)->prev;
	current = node;
	while (*data && ((*data)->token != PIPE))
	{
		if ((*data)->token == REDIRECT_IN || (*data)->token == REDIRECT_OUT
			|| (*data)->token == HEREDOC || (*data)->token == APPEND)
			node = create_redirect_node(data);
		else
		{
			arg_node = create_tree_node((*data)->token, (*data)->value);
			current->left = arg_node;
			current = arg_node;
		}
		*data = (*data)->prev;
	}
	return (node);
}

t_tree_node	*parse_expression(t_token **data)
{
	t_tree_node	*right_node;
	int			operator_type;
	char		*value;
	t_tree_node	*operator_node;

	right_node = parse_command(data);
	value = NULL;
	while (*data && ((*data)->token == PIPE))
	{
		operator_type = (*data)->token;
		value = ft_strdup((*data)->value);
		*data = (*data)->prev;
		operator_node = create_tree_node(operator_type, value);
		operator_node->right = right_node;
		operator_node->left = parse_expression(data);
		right_node = operator_node;
		free(value);
		value = NULL;
	}
	return (right_node);
}

void	parse(t_token *data)
{
	t_tree_node	*root;
	t_token		*last_token;

	last_token = get_last_token(data);
	root = parse_expression(&last_token);
	//printf("Tree Construction Complete\n");
	//print_tree(root, 0);
	free_list(&last_token);
	free_tree(root);
}
