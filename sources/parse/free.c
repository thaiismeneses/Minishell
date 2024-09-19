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
	node->left = NULL;
	free_tree(node->right);
	node->right = NULL;
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
	free(node);
	node = NULL;
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
		current->value = NULL;
		free(current);
		current = temp;
	}
	*data = NULL;
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

void	free_env_list(t_env_node *head)
{
	t_env_node	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->name_env);
		temp->name_env = NULL;
		free(temp->value_env);
		temp->value_env = NULL;
		free(temp->line_env);
		temp->line_env = NULL;
		free(temp);
		temp = NULL;
	}
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_main(t_main *main)
{
	if (!main)
		return ;
	free_env_list(main->env);
	main->env = NULL;
	free_list(&(main->token));
	main->token = NULL;
	free_tree(main->tree);
	main->tree = NULL;
	free(main->pwd);
	main->pwd = NULL;
	free(main->old_pwd);
	main->old_pwd = NULL;
	free(main);
}
