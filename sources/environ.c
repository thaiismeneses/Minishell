/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:13:19 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/15 19:08:12 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_node	*create_env_node(const char *env_var)
{
	t_env_node *new_node;
	char	*delimiter;
	
	delimiter = ft_strchr(env_var, '=');
	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("Failed to allocate memory for tree node");
		return (NULL);
	}
	new_node->line_env = ft_strdup(env_var);
	new_node->next = NULL;	
	if (delimiter != NULL)
	{
		*delimiter = '\0';
		new_node->name_env = ft_strdup(env_var);
		new_node->value_env = ft_strdup(delimiter + 1);
	}
	else
	{
		new_node->name_env = NULL;
		new_node->value_env = NULL;
	}
	return new_node;
}

void	append_env_node(t_env_node **head, char *line_env)
{
	t_env_node	*new_node;
	t_env_node	*temp;

	new_node = create_env_node(line_env);
	if (!new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

t_env_node	*build_environ(char **envp)
{
	t_env_node	*env_list;
	
	env_list = NULL;
	while (*envp != NULL)
	{
		append_env_node(&env_list, *envp);
		envp++;
	}
	return (env_list);
}