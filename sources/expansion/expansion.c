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
char	*strjoin_shell(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
	{
		result[j + i] = s2[i];
		i++;
	}
	result[j + i] = '\0';
	return (result);
}

int subst_env_var(t_token *node, int start, int length, t_main *main)
{
    char    *env_name;
    char	*value_var;
    char	*new_value;
    char	*before;
    char    *after;

    env_name = ft_substr(node->value, start, length);
    if (!env_name)
	    return (1);
    value_var = find_env(main->env, env_name);
    free(env_name);
    before = ft_substr(node->value, 0, start - 1);
    after = ft_strdup(&node->value[start + length]);
    if (value_var)
        new_value = strjoin_shell(before, value_var);
    else
        new_value = strjoin_shell(before, "\0");
    new_value = strjoin_shell(new_value, after);
    free(before);
    free(after);
    free(node->value);
    node->value = new_value;
    return (1);
}
int expansion(t_token *node, t_main *main)
{
    int i;
    int start;
    int expand;

    i = 0;
    expand = 0;
    while(node->value[i] != '\0')
    {
        if (node->value[i] == '$' && node->value[i + 1] == '?')
        {
            expand = 1;
            free(node->value);
            node->value = ft_itoa(last_status(-1));
            i += ft_strlen(node->value);
        }
        else if (node->value[i] == '$' && (ft_isalpha(node->value[i + 1]) 
        || node->value[i + 1] == '_'))
        {
            expand = 1;
            start = i + 1;
            i++;
            while (node->value[i] && (ft_isalnum(node->value[i]) ||
             node->value[i] == '_'))
                i++;
            subst_env_var(node, start, i - start, main);
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
		if (expansion(temp, main) && temp->value[0] != '\"')
			temp->token = 0;
		temp = temp->next;
	}
	temp = reorganize_cmd(header);
	main->token = temp;
}