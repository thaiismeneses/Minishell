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
        ft_putstr_fd("cd: HOME is not set\n", STDOUT_FILENO);
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
    char    *path;
    char    *new_path;

    i = 0;
    path = main->old_pwd;
    new_path = calloc(ft_strlen(path) + 1, sizeof (char));
    if (!new_path)
        return (1);
    while (path[i] != '\0')
        i++;
    while (i > 0 && path[i] != '/')
        i--;
    if (i == 0)
        ft_strncpy(new_path, path, ft_strlen(path));
    if (i > 0)
        ft_strncpy(new_path, path, i);
    new_path[i] = '\0';
    if (chdir(new_path))
    {
        free(new_path);
		return (1);
    }
    free(new_path);
	return (0);
}