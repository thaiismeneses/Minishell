/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:27 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:30 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *find_env(t_env_node *env, char *env_name)
{
    while(env)
    {
        if (!ft_strcmp(env->name_env, env_name))
            return(env->value_env);
        env = env->next;
    }
    return (NULL);
}

int    home_path(t_main *main)
{
    char    *path;

    path = find_env(main->env, "HOME");
    if (!path)
	{
        ft_putstr_fd("minishell: cd: HOME is not set\n", STDOUT_FILENO);
		return (1);
	}
	if (chdir(path))
		return (1);
	return (0);
}

int    old_path(t_main *main)
{
    char    *path;

    path = main->old_pwd;
	if (chdir(path))
		return (1);
	return (0);
}

int parent_path(t_main *main)
{
    int     i;
    char    *new_path;

    new_path = ft_strdup(main->pwd);
    if (!new_path)
        return (1);
    i = ft_strlen(new_path);
    while (i > 0 && new_path[i] != '/')
        i--;
    if (i == 0)
    {
        ft_strncpy(new_path, "/", 1);
        new_path[1] = '\0';
    }
    else
        new_path[i] = '\0';

    if (chdir(new_path) != 0)
    {
        perror("cd");
        free(new_path);
        return (1);
    }
    free(new_path);
    return (0);
}