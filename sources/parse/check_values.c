/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:52:48 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:52:48 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_order(t_token *data)
{
	while (data)
	{
		if (data && (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
				|| data->token == APPEND || data->token == HEREDOC))
		{
			if (data->next && data->next->token == CMD
				&& data->next->next == NULL)
			{
				return (0);
			}
			if (data->next->next && data->next->next->token == CMD)
			{
				return (1);
			}
		}
		data = data->next;
	}
	return (0);
}

char	*concatenate_cmd_tokens(t_token **data)
{
	char	*value;

	value = NULL;
	while (*data && ((*data)->token == CMD))
	{
		value = str_join(value, (*data)->value);
		free((*data)->value);
		(*data)->value = NULL;
		if ((*data)->next && ((*data)->next->token == CMD))
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
	value = NULL;
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

void	check_values(t_token *data, t_main *main)
{
	t_token	*new_list;

	new_list = NULL;
	if (is_in_order(data))
		data = swap_nodes(data);
	new_list = reorganize_cmd(data);
	main->token = new_list;
	expand_tokens(main);
	remove_quotes(main);
	main->tree = parse(main->token);
	free_list(&new_list);
	free_list(&data);
}
