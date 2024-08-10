/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:11:14 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/10 18:09:37 by thfranco         ###   ########.fr       */
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

	// t_token *node;
	// node = data;
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
	t_token	*new_list;
	char	*value;

	new_list = NULL;
	while (data)
	{
		value = NULL;
		if (data->token == CMD)
		{
			while (data && data->token == CMD)
			{
				value = str_join(value, data->value);
				if (data->next && data->next->token == CMD)
					value = str_join(value, " ");
				data = data->next;
			}
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

void	check_values(t_token *data)
{
	t_token	*new_list;

	if (is_in_order(data))
	{
		printf("SWAP\n");
		swap_nodes(data);
		new_list = reorganize_cmd(data);
		parse(new_list);
	}
	else
	{
		new_list = reorganize_cmd(data);
		parse(new_list);
	}
	//printf("NEW LIST\n");
	print_token_list(new_list);
	free_list(&new_list);
}
