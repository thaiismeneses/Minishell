/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:11:14 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/12 14:21:47 by thfranco         ###   ########.fr       */
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

void	check_values(t_token *data)
{
	int i;
	t_token	*new_list;
	char	**matrix;

	i = 0;
	new_list = NULL;
	if (is_in_order(data))
	{
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
	//print_token_list(new_list);
	//acho que vamos ter que transformar essa *new_list em uma matriz
	while(new_list)
	{
		matrix = ft_split(new_list->value, ' ');
		builtins(matrix);
		i++;
		new_list = new_list->next;
		free(matrix);
	}
	free_list(&new_list);
}