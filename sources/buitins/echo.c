/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:35 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:37 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_echo(char **token)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if(token[i] && !ft_strcmp(token[i], "-n"))
    {
        newline = 0;
        i = 2;
    }
    while (token[i])
    {
        ft_putstr_fd(token[i], STDOUT_FILENO);
        if (token[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (newline == 1)
        ft_putstr_fd("\n", STDOUT_FILENO);
    last_status(0);
    return (0);
}