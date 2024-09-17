/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:55:10 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:55:12 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	subst_env_var(t_token *node, int start, int length, t_main *main)
{
	char	*env_name;
	char	*value_var;
	char	*new_value;
	char	*before;
	char	*after;

	env_name = ft_substr(node->value, start, length);
	if (!env_name)
		return (1);
	value_var = find_env(main->env, env_name);
	free(env_name);
	before = ft_substr(node->value, 0, start - 1);
	after = ft_strdup(&node->value[start + length]);
	if (value_var)
		new_value = str_join(before, value_var);
	else
		new_value = str_join(before, "\0");
	new_value = str_join(new_value, after);
	free(after);
	free(node->value);
	node->value = ft_strdup(new_value);
	free(new_value);
	return (1);
}

int	handle_exit_status(t_token *node)
{
	int		expand;
	char	*temp;

	expand = 1;
	temp = ft_itoa(last_status(-1));
	if (node->value)
		free(node->value);
	node->value = ft_strdup(temp);
	free (temp);
	return (expand);
}

int	handle_expansion(t_token *node, int i, t_main *main)
{
	int	start;
	int	expand;

	expand = 1;
	start = i + 1;
	i++;
	while (node->value[i] && (ft_isalnum(node->value[i])
			|| node->value[i] == '_'))
		i++;
	subst_env_var(node, start, i - start, main);
	return (expand);
}

int	expansion(t_token *node, t_main *main)
{
	int	i;
	int	expand;

	i = 0;
	expand = 0;
	if (node->value[0] == '\'')
		return (expand);
	while (node->value[i] != '\0')
	{
		if (node->value[i] == '$' && node->value[i + 1] == '?')
		{
			expand = handle_exit_status(node);
			i = -1;
		}
		else if (node->value[i] == '$' && (ft_isalpha(node->value[i + 1])
				|| node->value[i + 1] == '_'))
		{
			expand = handle_expansion(node, i, main);
			i = -1;
		}
		i++;
	}
	return (expand);
}

void	expand_tokens(t_main *main)
{
	t_token	*header;
	t_token	*temp;

	temp = main->token;
	header = main->token;
	while (temp)
	{
		if (expansion(temp, main))
			temp->token = 0;
		temp = temp->next;
	}
	temp = reorganize_cmd(header);
	main->token = temp;
}
