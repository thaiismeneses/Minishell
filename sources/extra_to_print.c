/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_to_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:37:25 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 14:11:26 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_tree(t_tree_node *tree, int level) {
    if (!tree)
        return;

    // Print the current node with indentation based on the level
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("Node Level: %d\n", level);
    if (tree->value) {
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("Node Type: %d\n", tree->type);
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("Value: %s\n", tree->value);
    }

    // Print the left subtree
    if (tree->left) {
        for (int i = 0; i < level; i++)
            printf("  ");
        printf("Left:\n");
        print_tree(tree->left, level + 1);
    }

    // Print the right subtree
    if (tree->right) {
        for (int i = 0; i < level; i++)
            printf("  ");
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
void print_env_list(t_env_node *head) {
    t_env_node *temp = head;
    while (temp != NULL) {
        printf("Name: %s\nValue: %s\nLine: %s\n\n", temp->name_env, temp->value_env, temp->line_env);
        temp = temp->next;
    }
}
