/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:05:13 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/09/25 18:14:49 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	last_status(int status)
{
	static int	last;

	if (status > -1)
		last = status;
	return (last);
}

void	process_quote(t_token *data)
{
	int		i;
	char	quote;
	char	*temp;

	quote = data->value[0];
	i = 1;
	while (data->value[i] != '\0')
	{
		if (data->value[i++] == quote)
			break ;
	}
	temp = ft_substr(data->value, 1, i - 2);
	if (temp && ft_strcmp(temp, "\0"))
	{
		free(data->value);
		data->value = ft_strdup(temp);
		data->token = 0;
		free(temp);
	}
	else
	{
		data->token = 0;
		free(temp);
	}
}

static void	export_quote(t_token *token)
{
	char	*join;
	char	*old_value;
	t_token	*next_token;
	t_token	*data;

	data = token;
	if (!ft_strncmp(data->value, "export", 6)
		&& (data->next && (data->next->token == S_QUOTE
				|| data->next->token == D_QUOTE)))
	{
		old_value = data->value;
		join = ft_strjoin(data->value, data->next->value);
		free(old_value);
		data->value = join;
		next_token = data->next;
		data->next = next_token->next;
		free(next_token->value);
		free(next_token);
		data->token = 0;
	}
}

void	remove_quotes(t_main *main)
{
	t_token	*data;
	t_token	*head;
	t_token	*remove;

	data = main->token;
	head = data;
	export_quote(data);
	while (data)
	{
		if (!(ft_strcmp(data->value, "rm")) || !(ft_strcmp(data->value, "grep"))
			|| !(ft_strcmp(data->value, "echo")))
		{
			remove = data;
			while (remove)
			{
				if (remove->token == S_QUOTE || remove->token == D_QUOTE)
					remove->token = 0;
				remove = remove->next;
			}
		}
		if (data->token == S_QUOTE || data->token == D_QUOTE)
			process_quote(data);
		data = data->next;
	}
	main->token = reorganize_cmd(head);
}

int	builtins(char **token, char *path, t_main *main)
{
	if (!token || !token[0])
		return (0);
	if (!ft_strcmp(token[0], "exit"))
		return (ft_exit(token, path, main), 1);
	if (!ft_strcmp(token[0], "env"))
		return (ft_env(token, main), 1);
	if (!ft_strcmp(token[0], "export"))
		return (ft_export(token, main), 1);
	if (!ft_strcmp(token[0], "unset"))
		return (ft_unset(token, main), 1);
	if (!ft_strcmp(token[0], "pwd"))
	{
		ft_putstr_fd(main->pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (last_status(0), 1);
	}
	if (!ft_strcmp(token[0], "cd"))
		return (ft_cd(token, main), 1);
	if (!ft_strcmp(token[0], "echo"))
		return (ft_echo(token), 1);
	return (last_status(0), 0);
}
