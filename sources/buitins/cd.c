/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:18 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:21 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env_pwd(t_main *main, t_env_node *temp, char *pwd_line, char *oldpwd)
{
    if (!ft_strcmp(temp->name_env, "PWD"))
    {
        free(temp->value_env);
		free(temp->line_env);
        temp->value_env = ft_strdup(main->pwd);
        temp->line_env = ft_strdup(pwd_line);
    }
    else if (!ft_strcmp(temp->name_env, "OLDPWD"))
    {
        free(temp->value_env);
		free(temp->line_env);
        temp->value_env = ft_strdup(main->old_pwd);
        temp->line_env = ft_strdup(oldpwd);
        return (1);
    }
    return (0);
}

void    update_pwd(t_main *main)
{
	char	pwd[PATH_MAX];
    t_env_node  *temp;
    int old_pwd;
    char    *oldpwd;
    char    *pwd_line;

    old_pwd = 0;
    temp = main->env;
	getcwd(pwd, sizeof(pwd));
    free(main->old_pwd);
	main->old_pwd = main->pwd;
    main->pwd = ft_strdup(pwd);
    oldpwd = ft_strjoin("OLDPWD=", main->old_pwd);
    pwd_line = ft_strjoin("PWD=", main->pwd);
    while (temp != NULL)
    {
        old_pwd = env_pwd(main, temp, pwd_line, oldpwd);
        temp = temp->next;
    }
    if (!old_pwd)
        append_env_node(&main->env, oldpwd);
    free(oldpwd);
    free(pwd_line);
}

int chdir_error(char *token)
{
    ft_putstr_fd("cd: ", STDOUT_FILENO);
    perror(token);
    last_status(1);
    return (1);
}

int ft_cd(char **token, t_main *main)
{
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (token[i])
        i++;
    if (i > 2)
        return (handle_too_many_args());
    else if (i == 1 || token[1][0] == '\0' || !ft_strcmp(token[1], "~"))
        ret = home_path(main);
    else if (i == 1 && !ft_strcmp(token[1], "-"))
        ret = old_path(main);
    else if (i == 1 && !ft_strcmp(token[1], ".."))
        ret = parent_path(main);
    else
    {
        if (chdir(token[1]) != 0)
            ret = chdir_error(token[1]);
    }
    if (ret == 0)
        update_pwd(main);
    return (ret);
}
