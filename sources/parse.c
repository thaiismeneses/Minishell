/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:58:59 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/09 09:58:05 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tree(t_tree_node *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

t_tree_node	*create_tree_node(t_type_cmd type, char *value)
{
	t_tree_node	*node;

	node = calloc(1, sizeof(t_tree_node));
	if (!node)
	{
		perror("Failed to allocate memory for tree node");
		return (NULL);
	}
	node->type = type;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
 }

char	*str_join(char *dest, char *src)
{
	char *result;
	if (!src)
		return (dest);
	if (!dest)
		return (ft_strdup(src));
	result = ft_strjoin(dest, src);
	return (result);
}
//working
t_tree_node	*parse_command(t_token **data)
{
	t_tree_node	*node;
	t_tree_node	*current;
	t_tree_node	*arg_node;
	char *value;


	if (*data == NULL)
		return (NULL);
	node = create_tree_node((*data)->token, (*data)->value);
	*data = (*data)->prev;
	current = node;
	while (*data && ((*data)->token != PIPE))
	{
		value = NULL; 
		if ((*data)->token == REDIRECT_IN || (*data)->token == REDIRECT_OUT ||
			(*data)->token == HEREDOC || (*data)->token == APPEND)
		{
			value = str_join(value, (*data)->prev->value);
			value = str_join(value, (*data)->value);
			value = str_join(value, (*data)->next->value);
			arg_node = create_tree_node(COMMAND_SUBSTITUTION, value);
			free(value);
			node = arg_node;
		}
		else
		{
			arg_node = create_tree_node((*data)->token,(*data)->value);
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
	while (*data && ((*data)->token == PIPE))
	{
		operator_type = (*data)->token;
		value = (*data)->value;
		*data = (*data)->prev;
		operator_node = create_tree_node(operator_type, value);
		operator_node->right = right_node;
		operator_node->left = parse_expression(data);
		right_node = operator_node;
	}
	return (right_node);
}


void	parse(t_token *data)
{
	t_tree_node	*root;
	t_token		*last_token;

	last_token = get_last_token(data);
	root = parse_expression(&last_token);
	printf("Tree Construction Complete\n");
	print_tree(root, 0);
	free_tree(root);
}

