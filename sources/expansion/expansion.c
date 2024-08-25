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

void	expand_tokens(t_main *main)
{
	t_token	*header;
	t_token	*temp;

	header = main->token;
	temp = header;
	while (temp)
	{
		if (expansion(temp->value, main))
			temp->token = 0;
		temp = temp->next;
	}
	temp = reorganize_cmd(header);
	free_list(&header);
	main->token = temp;
}

int	expansion(char *token, t_main *main) //precisa fazer a expansão do $?
{
	char	*env_var;
	char	*value_var;

	if (token[0] == '$' && ft_strlen(token) > 1) //aspas duplas
	{
		env_var = ft_calloc(ft_strlen(token), sizeof(char));
		if (!env_var)
			return (1);
		str_slice(env_var, token);
		value_var = find_env(main->env, env_var);
		free(env_var);
		if (value_var)
		{
			free(token);
			token = ft_strdup(value_var);
			if (!token)
				return (0);
		}
		return (1);
	}
	return (0);
}
