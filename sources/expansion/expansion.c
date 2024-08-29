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

int	last_status(int status)
{
	static int last;

	if (status > -1)
		last = status;
	return (last);
}

int subst_env_var(t_token *node, int start, int length, t_main *main)
{
    char    *env_name;
    char	*value_var;
    char	*new_value;
    char	*before;

    env_name = ft_substr(node->value, start, length);
    if (!env_name)
	    return (1);
    value_var = find_env(main->env, env_name);
    free(env_name);
    if (value_var)
    {
        before = ft_substr(node->value, 0, start - 1);
        new_value = ft_strjoin(before, value_var);
        free(before);
        free(node->value);
        node->value = new_value;
        return (1);
    }
    else
    {
        before = ft_substr(node->value, 0, start - 1);
        new_value = ft_strjoin(before, "\0");
        free(before);
        free(node->value);
        node->value = new_value;
        return (1);
    }
    return (0);
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
        if (node->value[i] == '$' && node->value[i + 1] == '?')
        {
            free(node->value);
            node->value = ft_itoa(last_status(-1));
        }
        else if (node->value[i] == '$' && (ft_isalpha(node->value[i + 1]) 
        || node->value[i + 1] == '_'))
        {
            start = i + 1;
            i++;
            while (node->value[i] && (ft_isalnum(node->value[i]) ||
             node->value[i] == '_'))
                i++;
            if (subst_env_var(node, start, i - start, main))
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
	while (temp)
	{
		if (!expansion(temp, main) && temp->value[0] != '\"')
			temp->token = 0;
		temp = temp->next;
	}
	temp = reorganize_cmd(header);
	main->token = temp;
}