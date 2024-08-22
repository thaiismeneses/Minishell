/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:54 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:56 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_node_export(char *token, t_main *main, int i)
{
    t_env_node *temp;
    t_env_node *prev;

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

void    utils_export(char **token, t_main *main, int type)
{
    t_env_node *temp;

    temp = main->env;
    if (type == 1)
    {
        while (temp != NULL) 
        {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            ft_putstr_fd(temp->line_env, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
            temp = temp->next;
        }
    }
    if (type == 2) 
    {
        ft_putstr_fd("export: '", STDOUT_FILENO);
        ft_putstr_fd(token[1], STDOUT_FILENO);
        ft_putstr_fd("': need '=' after variable name\n", STDOUT_FILENO);
    }
    if (type == 3)
    {
        ft_putstr_fd("export: '", STDOUT_FILENO);
        ft_putstr_fd(token[1], STDOUT_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
    }
}
int    export_env(char **token, t_main *main)
{
    int i;
    t_env_node  *temp;

    i = 0;
    temp = main->env;
    while (token[1][i] != '\0' && token[1][i] != '=')
        i++;
    if (token[1][i] == '=')
    {
        while (temp != NULL)
        {
            if (!ft_strncmp(token[1], temp->name_env, i) && temp->name_env[i] == '\0')
            {
                remove_node_export(token[1], main, i);
                break ;
            }
            temp = temp->next;
        }
        append_env_node(&main->env, token[1]);
    }
    else
        return(utils_export(token, main, 2), 1);
    return (0);
}

int ft_export(char **token, t_main *main)
{
    if (!token[1])
    {
        utils_export(token, main, 1);
        return (0);
    }
    if (!ft_isalpha(token[1][0]) && token[1][0] != '_')
    {
        utils_export(token, main, 3);
        return (1);
    }
    else
    {
       if (!export_env(token, main))
            return (1);
    }
    return(0);
}
