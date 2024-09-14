/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:52:36 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:56:09 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_first_token_redirect(t_token *data)
{
	if (data && (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
			|| data->token == APPEND || data->token == HEREDOC))
	{
		return (1);
	}
	return (0);
}

int	is_redirect(int token)
{
	if (token == REDIRECT_IN || token == REDIRECT_OUT
		|| token == APPEND || token == HEREDOC)
	{
		return (1);
	}
	return (0);
}

t_token	*get_next_redirect(t_token *data)
{
	t_token	*current;

	current = data;
	while (!is_redirect(current->token))
		current = current->next;
	return (current);
}

t_token *get_until_cmd(t_token *data)
{
	t_token	*current;

	current = data;
	while (current->token != CMD)
		current = current->next;

	return (current);
}

static t_token	*swap_init_redirect(t_token *data)
{
	t_token	*temp;
	t_token	*last;
	t_token	*cmd;
	t_token	*current;

	while (data)
	{
		if ((data->token == REDIRECT_IN || data->token == REDIRECT_OUT
				|| data->token == APPEND || data->token == HEREDOC)
			&& data->next->next && data->next->next->token == CMD)
		{
			temp = data;
			cmd = data->next->next;
			printf("CMD\n");
			print_token_list(cmd);
			current = get_next_redirect(data->next->next);
			while (cmd->token == CMD && cmd->next && cmd->next->token == CMD)
			{
				cmd = cmd->next;
			}
			cmd->next = temp;
			temp->next->prev = cmd;
			cmd->next->next = current;
			printf("CMD DEPOIS\n");
			print_token_list(cmd);
			if (data->prev)
				data->prev->next = data->next->next;
			if (data->prev)
				data->next->next->prev = data->prev;


			last = get_last_token(data);
			last->next = temp;
			temp->prev = last;
			temp->next->next = NULL;
			data = data->next;
		}
		else
			data = data->next;
	}
	return (last);
}

// static t_token	*swap_init_redirect(t_token *data)
// {
// 	t_token	*temp;
// 	t_token	*last;
// 	t_token	*cmd;

// 	while (data)
// 	{
// 		if ((data->token == REDIRECT_IN || data->token == REDIRECT_OUT
// 				|| data->token == APPEND || data->token == HEREDOC)
// 			&& data->next->next && data->next->next->token == CMD)
// 		{
// 			temp = data;
// 			if (data->prev)
// 				data->prev->next = data->next->next;
// 			if (data->prev)
// 				data->next->next->prev = data->prev;
// 			cmd = get_until_cmd(data->next->next);
// 			printf("cmd: %s\n", cmd->value);
// 			last = get_last_token(data);
// 			last->next = temp;
// 			temp->prev = last;
// 			temp->next->next = NULL;
// 			data = data->next;
// 		}
// 		else
// 			data = data->next;
// 	}
// 	return (last);
// }

t_token	*swap_nodes(t_token *data)
{
	t_token	*temp;
	t_token	*last;
	t_token	*head;

	head = data;
	if (is_first_token_redirect(head))
		return (swap_init_redirect(head));
	while (head)
	{
		if ((head->token == REDIRECT_IN || head->token == REDIRECT_OUT
				|| head->token == APPEND || head->token == HEREDOC)
			&& head->next->next && head->next->next->token == CMD)
		{
			temp = head;
			head->prev->next = head->next->next;
			head->next->next->prev = head->prev;
			last = get_last_token(head);
			last->next = temp;
			temp->prev = last;
			temp->next->next = NULL;
		}
		head = head->next;
	}
	return (data);
}

