/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:42:20 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:17:58 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_tree_node *node)
{
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	free(node->value);
	free(node);
}

void	free_list(t_token **data)
{
	t_token	*current;
	t_token	*temp;

	if (!data || !(*data))
		return ;
	current = *data;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	*data = NULL;
}

void	free_env_list(t_env_node *head)
{
	t_env_node	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name_env);
		free(temp->value_env);
		free(temp->line_env);
		free(temp);
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
