/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:40:26 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/09/17 11:59:44 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_node_export(char *token, t_main *main, int i)
{
	t_env_node	*temp;
	t_env_node	*prev;

	temp = main->env;
	prev = NULL;
	while (temp != NULL)
	{
		if (!ft_strncmp(token, temp->name_env, i) && temp->name_env[i] == '\0')
		{
			if (prev == NULL)
				main->env = temp->next;
			else
				prev->next = temp->next;
			free(temp->name_env);
			free(temp->value_env);
			free(temp->line_env);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	errors_export(char *token, int type)
{
	if (type == 1)
	{
		ft_putstr_fd("export: '", STDOUT_FILENO);
		ft_putstr_fd(token, STDOUT_FILENO);
		ft_putstr_fd("': need '=' after variable name\n", STDOUT_FILENO);
		last_status(1);
	}
	if (type == 2)
	{
		ft_putstr_fd("export: '", STDOUT_FILENO);
		ft_putstr_fd(token, STDOUT_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		last_status(1);
	}
}

void	util_export(t_main *main)
{
	t_env_node	*temp;

	temp = main->env;
	while (temp != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(temp->line_env, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		temp = temp->next;
	}
	last_status(0);
}

int	export_env(char *token, t_main *main)
{
	int			i;
	t_env_node	*temp;

	i = 0;
	temp = main->env;
	while (token[i] != '\0' && token[i] != '=')
		i++;
	if (token[i] == '=' && ft_isalpha(token[0]))
	{
		export_util(temp, token, i, main);
	}
	else
		return (errors_export(token, 1), 1);
	last_status(0);
	return (0);
}

int	ft_export(char **token, t_main *main)
{
	int	i;
	int flag;

	i = 1;
	flag = 1;
	if (!token[1])
	{
		util_export(main);
		return (0);
	}
	while (token[i])
	{
		flag = export_env(token[i], main);
		i++;
		if (!token[i] && flag == 1)
			return (1);
	}
	return (0);
}
