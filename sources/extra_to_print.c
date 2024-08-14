/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_to_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:37:25 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/12 20:13:39 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_tree_node *tree, int level)
{
	int	i;

	i = 0;
	if (!tree)
		return ;
	while (i < level)
	{
		printf("  ");
		i++;
	}
	printf("Node Level: %d\n", level);
	if (tree->value)
	{
		i = 0;
		while (i < level)
		{
			printf("  ");
			i++;
		}
		printf("Node Type: %d\n", tree->type);
		i = 0;
		while (i < level)
		{
			printf("  ");
			i++;
		}
		printf("Value: %s\n", tree->value);
	}
	if (tree->left)
	{
		i = 0;
		while (i < level)
		{
			printf("  ");
			i++;
		}
		printf("Left:\n");
		print_tree(tree->left, level + 1);
	}
	if (tree->right)
	{
		i = 0;
		while (i < level)
		{
			printf("  ");
			i++;
		}
		printf("Right:\n");
		print_tree(tree->right, level + 1);
	}
}

void	print_token_list(t_token *head)
{
	t_token	*current;

	current = head;
	printf("Lista de Tokens:\n");
	while (current != NULL)
	{
		printf("Token: %s\n", current->value);
		printf("Tipo: %d\n", current->token);
		current = current->next;
	}
}

void	print_error(char *msg, char *value)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("\'\n", 2);
	if (errno != 0)
		perror("");
}

void	print_env_list(t_env_node *head)
{
	t_env_node	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", temp->line_env);
		temp = temp->next;
	}
}
