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

/*void	str_slice(char *dest, const char *src)
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

int	expansion(t_token *node, t_main *main)
{
	char	*env_var;
	char	*value_var;

	if (node->value[0] == '$' && ft_strlen(node->value) > 1)
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
}*/
void subst_env_var(t_token *node, int start, int length, t_main *main)
{
    char    *env_name;
    char	*value_var;
    char	*new_value;
    char	*before;
    char	*after;

    env_name = ft_substr(node->value, start, length);
    if (!env_name)
	    return ;
    value_var = find_env(main->env, env_name);
    free(env_name);
    if (value_var)
    {
        before = ft_substr(node->value, 0, start - 1);
        after = ft_strdup(node->value + start + length);
        new_value = ft_strjoin(before, value_var);
        free(before);
        before = ft_strjoin(new_value, after);
        free(new_value);
        free(after);
        free(node->value);
        node->value = before;
    }
}
int expansion(t_token *node, t_main *main)
{
    int i;
    int start;
    t_token *temp;

    i = 0;
    temp = node;
    while(node->value[i] != '\0')
    {
        if (node->value[i] == '\'')
        {
            i++;
            while(node->value[i] != '\'' && node->value[i] != '\0')
            {
                if (node->value[i] == '$' && (ft_isalpha(node->value[i + 1]) || node->value[i + 1] == '_'))
                {
                    start = i + 1;
                    i++;
                    while(node->value[i] && (!(ft_isalpha(node->value[i])) ||
                    !(ft_isdigit(node->value[i])) || node->value[i] == '_'))
                        i++;
                    subst_env_var(node, start, i - start, main);
                }
            }
            i++;
        }
        else if (node->value[i] == '$' && (ft_isalpha(node->value[i + 1]) || node->value[i + 1] == '_'))
        {
            start = i + 1;
            i++;
            while (node->value[i] && (ft_isalnum(node->value[i]) || node->value[i] == '_'))
                i++;
            subst_env_var(node, start, i - start, main);
            expansion(temp, main);
        }
        else
            i++;
    }
    return (0);
}

void	expand_tokens(t_main *main)
{
	t_token	*header;
	t_token	*temp;

	temp = main->token;
	header = main->token;
    print_token_list(main->token);
	while (temp)
	{
		if (!expansion(temp, main) && temp->value[0] != '\"')
			temp->token = 0;
		temp = temp->next;
	}
	temp = reorganize_cmd(header);
	main->token = temp;
}

//Problema: Quando não existe a env_var