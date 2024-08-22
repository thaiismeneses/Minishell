/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:34:00 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:34:02 by lfuruno-         ###   ########.fr       */
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
