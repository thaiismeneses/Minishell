/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 09:41:15 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/24 18:19:33 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_token	*temp;

	temp = data;
	while (temp)
	{
		if (temp->token == PIPE || is_redirect(temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	handle_command(t_token **new, char *cmd, int flag, t_token **tmp)
{
	char	*new_cmd;

	if (flag == 1)
		add_node(new, COMMAND_SUBSTITUTION, cmd);
	else
		add_node(new, CMD, cmd);
	if (*tmp && (*tmp)->token == PIPE)
	{
		new_cmd = ft_strdup((*tmp)->value);
		add_node(new, (*tmp)->token, new_cmd);
		free(new_cmd);
		*tmp = (*tmp)->next;
	}
}

int	process_tokens(t_token **tmp, char **cmd)
{
	int		flag;
	char	*value;

	flag = 0;
	while (*tmp && (*tmp)->token != PIPE)
	{
		if (is_redirect(*tmp) == 1)
			flag = 1;
		value = ft_strdup((*tmp)->value);
		*cmd = join_cmd(*cmd, value, (*tmp)->next
				&& (*tmp)->next->token != PIPE);
		free(value);
		value = NULL;
		*tmp = (*tmp)->next;
	}
	return (flag);
}

t_token	*append_command(t_token *data)
{
	char	*cmd;
	t_token	*tmp;
	int		flag;
	t_token	*new;

	cmd = NULL;
	new = NULL;
	if (!has_redirs(data))
		return (data);
	tmp = data;
	while (tmp)
	{
		flag = process_tokens(&tmp, &cmd);
		handle_command(&new, cmd, flag, &tmp);
		free(cmd);
		cmd = NULL;
	}
	free_list_two(data);
	return (new);
}
