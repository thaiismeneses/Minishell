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

void	export_util(t_env_node *temp, char *token, int i, t_main *main)
{
	char	*token_one;

	token_one = ft_strdup(token);
	while (temp != NULL)
	{
		if (!ft_strncmp(token, temp->name_env, i)
			&& temp->name_env[i] == '\0')
		{
			remove_node_export(token, main, i);
			break ;
		}
		temp = temp->next;
	}
	append_env_node(&main->env, token_one);
	free(token_one);
}
