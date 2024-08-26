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

void	str_slice(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (src[i])
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

int	expansion(t_token *node, t_main *main) //precisa fazer a expansão do $?
{
	char	*env_var;
	char	*value_var;

	if (node->value[0] == '$' && ft_strlen(node->value) > 1) //aspas duplas
	{
		env_var = ft_calloc(ft_strlen(node->value), sizeof(char));
		if (!env_var)
			return (1);
		str_slice(env_var, node->value);
		value_var = find_env(main->env, env_var);
		free(env_var);
		if (value_var)
		{
			node->value = ft_strdup(value_var);
			if (!node->value)
				return (0);
		}
		return (1);
	}
	return (0);
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