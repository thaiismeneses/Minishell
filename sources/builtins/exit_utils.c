/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:39:42 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/09/17 11:39:44 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	numeric_arg(char **token, t_main *main, char *path)
{
	error_exit(token[1], 2);
	last_status(2);
	ft_free_tab(token);
	token = NULL;
	free(path);
	path = NULL;
	free_main(main);
	exit(2);
}

void	exit_cmd(char **token, t_main *main, char *path)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (token[1])
		exit_code = get_number(ft_atol(token[1]));
	last_status(exit_code);
	ft_free_tab(token);
	token = NULL;
	free(path);
	path = NULL;
	free_main(main);
	exit(exit_code);
}
