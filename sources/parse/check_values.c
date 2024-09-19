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

char	*concatenate_cmd_tokens(t_token **data)
{
	char	*value;
	char	*cmd;

	value = NULL;
	while (*data && ((*data)->token == CMD))
	{
		cmd = ft_strdup((*data)->value);
		value = str_join(value, cmd);
		free(cmd);
		free((*data)->value);
		(*data)->value = NULL;
		if ((*data)->next && ((*data)->next->token == CMD))
			value = str_join(value, " ");
		*data = (*data)->next;
	}
	return (value);
}

t_token	*handle_cmd_token(t_token **data, t_token *new_list)
{
	char	*value;

	if ((*data)->token == CMD)
	{
		value = concatenate_cmd_tokens(data);
		new_list = set_token_list(new_list, value, 0);
		free(value);
		value = NULL;
	}
	else
	{
		value = ft_strdup((*data)->value);
		new_list = set_token_list(new_list, value, (*data)->token);
		free(value);
		*data = (*data)->next;
	}
	return (new_list);
}

t_token	*reorganize_cmd(t_token *data)
{
	t_token	*new_list;
	t_token	*node;

	new_list = NULL;
	node = data;
	while (data)
	{
		new_list = handle_cmd_token(&data, new_list);
	}
	if (node)
		free_list(&node);
	return (new_list);
}

void	check_values(t_token *data, t_main *main)
{
	t_token	*new_list;
	t_token	*node;
	t_token	*tmp;

	node = data;
	new_list = NULL;
	new_list = reorganize_cmd(node);
	main->token = new_list;
	if (!has_heredoc(main->token))
	{
		expand_tokens(main);
		remove_quotes(main);
	}
	tmp = NULL;
	tmp = append_command(main->token);
	main->token = tmp;
	main->tree = parse(main->token);
}
