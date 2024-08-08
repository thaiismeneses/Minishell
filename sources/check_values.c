/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:11:14 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/08 20:37:51 by thfranco         ###   ########.fr       */
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

	while (data)
	{
		printf("SWAP\n");
		if (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
			|| data->token == APPEND || data->token == HEREDOC)
		{
			if (data->next->next && data->next->next->token == CMD)
			{
				temp = data;
				printf("temp: %s\n", temp->value);
				data->prev->next = data->next->next;
				printf("data->prev->next: %s\n", data->prev->next->value);
				data->next->next->prev = data->prev;
				printf("data->next->next->prev: %s\n", data->next->next->prev->value);
				last = get_last_token(data);
				printf("last: %s\n", last->value);
				last->next = temp;
				printf("last->next: %s\n", last->next->value);
				temp->prev = last;
				temp->next = NULL;
				//data  = get_last_token(data);
			}
			data = data->next;
		}
		else
			data = data->next;
	}
	printf("NEW LIST\n");
	print_token_list(data);
}



void	check_values(t_token *data)
{
	if (is_in_order(data))
	{
		printf("AQUIIII\n");
		swap_nodes(data);
	}
}

