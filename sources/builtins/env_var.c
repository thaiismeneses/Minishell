/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:39:14 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/09/17 11:57:35 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **token, t_main *main)
{
	t_env_node	*temp;

	temp = main->env;
	if (token[1])
	{
		ft_putstr_fd("env: '", STDOUT_FILENO);
		ft_putstr_fd(token[1], STDOUT_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDOUT_FILENO);
		last_status(127);
		return (1);
	}
	while (temp != NULL)
	{
		ft_putstr_fd(temp->line_env, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = temp->next;
	}
	last_status(0);
	return (0);
}
