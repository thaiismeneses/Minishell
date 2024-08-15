/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:11:14 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/15 19:00:35 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_order(t_token *data)
{
	while (data)
	{
		if (data && (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
				|| data->token == APPEND || data->token == HEREDOC))
		{
			if (data->next->next && data->next->next->token == CMD)
			{
				return (1);
			}
		}
		data = data->next;
	}
	return (0);
}

void	swap_nodes(t_token *data)
{
	t_token	*temp;
	t_token	*last;
	
	while (data)
	{
		if (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
			|| data->token == APPEND || data->token == HEREDOC)
		{
			if (data->next->next && data->next->next->token == CMD)
			{
				temp = data;
				data->prev->next = data->next->next;
				data->next->next->prev = data->prev;
				last = get_last_token(data);
				last->next = temp;
				temp->prev = last;
				temp->next->next = NULL;
			}
			data = data->next;
		}
		else
			data = data->next;
	}
}

char	*concatenate_cmd_tokens(t_token **data)
{
	char	*value;

	value = NULL;
	while (*data && (*data)->token == CMD)
	{
		value = str_join(value, (*data)->value);
		if ((*data)->next && (*data)->next->token == CMD)
			value = str_join(value, " ");
		*data = (*data)->next;
	}
	return (value);
}

t_token	*reorganize_cmd(t_token *data)
{
	t_token	*new_list;
	char	*value;

	new_list = NULL;
	while (data)
	{
		if (data->token == CMD)
		{
			value = concatenate_cmd_tokens(&data);
			new_list = set_token_list(new_list, value, 0);
			free(value);
		}
		else
		{
			new_list = set_token_list(new_list, data->value, data->token);
			data = data->next;
		}
	}
	return (new_list);
}

void	check_values(t_token *tokens, t_main *main)
{
	t_token	*new_list;
	t_tree_node *tree;

	new_list = NULL;
	if (is_in_order(tokens))
	{
		swap_nodes(tokens);
		new_list = reorganize_cmd(tokens);
		main->tokens = new_list;
		tree = parse(new_list);
		main->tree = tree;
		execute_cmd(tree, main);
	}
	else
	{
		new_list = reorganize_cmd(tokens);
		main->tokens = new_list;
		tree = parse(new_list);
		main->tree = tree;
		execute_cmd(tree, main);
	}
	//printf("NEW LIST\n");
	//print_token_list(new_list);
	free_list(&new_list);
}
