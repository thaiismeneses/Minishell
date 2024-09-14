/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:48 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:50 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_exit(char *token, int option)
{
    ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (option == 1)
	{
        (void)token;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
        return (1);
	}
	else
	{
        ft_putstr_fd("minishell: ", STDOUT_FILENO);
        ft_putstr_fd(token, STDOUT_FILENO);
        ft_putstr_fd(" : numeric argument required\n", STDOUT_FILENO);
        return (2);
	}
}

int is_number(char *token)
{
    int i;

    i = 0;
    if (token[i] == '-' || token[i] == '+')
        i++;
    if (token[i] == '\0')
        return (0);
    while (token[i])
    {
        if (!ft_isdigit(token[i]))
            return (0);
        i++;
    }
    if (i > 20)
        return (0);
    return (1);
}
long    get_number(long number)
{
    while(number < 0)
        number = 256 + number;
    return (number);
}
int    ft_exit(char **token, char *path, t_main *main)
{
    if(token[1] && token[2])
    {
        last_status(1);
        return(error_exit(token[1], 1));
    }
    else if (token[1] && !is_number(token[1]))
        numeric_arg(token, main, path);
    else
        exit_cmd(token, main, path);
    exit(last_status(-1));
}