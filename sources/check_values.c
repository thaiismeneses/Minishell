/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:11:14 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/09 11:56:46 by thfranco         ###   ########.fr       */
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
	t_token *temp;
	t_token *last;
	t_token *node;

	node = data;
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

t_token	*reorganize_cmd(t_token *data)
{
	t_token *new_list;
	char *value;
	
	while (data)
	{
		if (data->token == CMD)
		{
		printf("NEW_LIST\n");
			while (data->token == CMD)
			{
				value = str_join(value, data->value);
				printf("VALUE: %s\n", value);
				data = data->next;
			}
			add_node(&new_list, data->token, value);		
		}
		else
			add_node(&new_list, data->token, value);		

		data = data->next;
	}
	return (new_list);
}

void	check_values(t_token *data)
{
	t_token	*new_list;
	
	if (is_in_order(data))
	{	
		printf("SWAP\n");
		swap_nodes(data);
	}
	else
	{
		new_list = reorganize_cmd(data);
		printf("NEW LIST\n");
		print_token_list(new_list);
	}
}

