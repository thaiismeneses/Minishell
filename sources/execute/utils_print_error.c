/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:18:22 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/25 16:18:29 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_exc(char *msg, char *cmd)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}
