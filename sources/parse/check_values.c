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

// int	is_in_order(t_token *data)
// {
// 	while (data)
// 	{
// 		if (data && (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
// 				|| data->token == APPEND || data->token == HEREDOC))
// 		{
// 			if (data->next && data->next->token == CMD
// 				&& data->next->next == NULL)
// 			{
// 				return (0);
// 			}
// 			if (data->next->next && data->next->next->token == CMD)
// 			{
// 				return (1);
// 			}
// 		}
// 		data = data->next;
// 	}
// 	return (0);
// }

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

int	is_redirect(t_token *data)
{
	if (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
			|| data->token == APPEND || data->token == HEREDOC)
	{
		return (1);
	}
	return (0);
}

int	has_redirs(t_token *data)
{
	t_token *temp;

	temp = data;
	while (temp)
	{
		if (temp->token == PIPE || is_redirect(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}

t_token	*append_command(t_token *data)
{
	char *cmd;
	t_token *tmp;
	int flag;
	t_token	*new;
	char *value;

	flag = 0;
	cmd = NULL;
	new = NULL;
	value = NULL;
	if (!has_redirs(data))
		return (data);
	tmp = data;
	while (tmp)
	{
		flag = 0;
		while (tmp && tmp->token != PIPE)
		{
			if (is_redirect(tmp) == 1)
				flag = 1;
			value = ft_strdup(tmp->value);
			cmd = str_join(cmd, value);
			free(value);
			value = NULL;
			if (tmp->next && tmp->next->token != PIPE)
				cmd = str_join(cmd, " ");
			tmp = tmp->next;
			printf("CMD: %s\n", cmd);
		}
		if (flag == 1)
		{
			printf("AQUII\n");
			add_node(&new, COMMAND_SUBSTITUTION, cmd);
		}
		else
		{
			printf("AQUIICMD\n");
			add_node(&new, CMD, cmd);
		}
		if (tmp && tmp->token == PIPE)
		{

			add_node(&new, tmp->token, tmp->value);
			tmp = tmp->next;
		}
		free(cmd);
		cmd = NULL;
		//tmp = tmp->next;
	}
	free_list_two(data);
	return (new);
}

void	check_values(t_token *data, t_main *main)
{
	t_token	*new_list;
	t_token	*node;
	t_token *tmp;

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
	//print_token_list(main->token);
	main->tree = parse(main->token);
	print_tree(main->tree, 0);
}
