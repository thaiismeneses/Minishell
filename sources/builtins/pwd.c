/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:40:36 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/09/17 12:00:11 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_pwd(t_main *main)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	main->pwd = ft_strdup(pwd);
	main->old_pwd = ft_strdup(pwd);
}
