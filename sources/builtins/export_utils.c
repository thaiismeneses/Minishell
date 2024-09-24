/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:35:53 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/24 11:44:53 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_util(t_env_node *temp, char **token, int i, t_main *main)
{
	char	*token_one;
	char	*join;

	token_one = ft_strdup(token[1]);
	while (temp != NULL)
	{
		if (!ft_strncmp(token[1], temp->name_env, i)
			&& temp->name_env[i] == '\0')
		{
			remove_node_export(token[1], main, i);
			break ;
		}
		temp = temp->next;
	}
	join = str_join(token_one, token[2]);
	append_env_node(&main->env, join);
	free(join);
}
