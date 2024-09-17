/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/20 14:48:54 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:15:38 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_start_end(t_token *data)
{
	if (data->token == PIPE)
	{
		print_error("syntax error near unexpected token `", data->value);
		return (1);
	}
	while (data->next != NULL)
		data = data->next;
	if (data->next == NULL)
	{
		if (data->token == REDIRECT_IN || data->token == REDIRECT_OUT
			|| data->token == APPEND || data->token == HEREDOC)
		{
			print_error("syntax error near unexpected token `", "newline");
			return (1);
		}
	}
	return (0);
}

static int	find_closing_quote(char *value, char quote)
{
	int	i;

	i = 1;
	while (value[i] != '\0')
	{
		if (value[i++] == quote)
			return (1);
	}
	return (0);
}

int	check_quotes(t_token *data)
{
	while (data)
	{
		if (data->token == S_QUOTE || data->token == D_QUOTE)
		{
			if (!find_closing_quote(data->value, data->value[0]))
			{
				ft_putstr_fd("syntax: only parses closed quotes\n", 2);
				return (1);
			}
		}
		data = data->next;
	}
	return (0);
}

int	has_error(t_token *data)
{
	if (data->value == NULL || check_append(data) || check_redirect_in(data)
		|| check_redirect_out(data) || check_heredoc(data) || check_pipe(data)
		|| check_start_end(data) || check_quotes(data))
	{
		free_list(&data);
		return (last_status(2), 0);
	}
	return (1);
}
