#include "../../includes/minishell.h"

void    update_pwd(t_main *main)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
    free(main->old_pwd);
	main->old_pwd = main->pwd;
    main->pwd = ft_strdup(pwd);
}

int ft_cd(char **token, t_main *main)
{
    int ret;

    ret = 0;
    if (!token[1] || token[1][0] == '\0' || !ft_strcmp(token[1], "~"))
        ret = home_path(main);
    else if (!ft_strcmp(token[1], "-"))
        ret = old_path(main);
    else if (!ft_strcmp(token[1], ".."))
        ret = parent_path(main);
    else
    {
        if (chdir(token[1]) != 0)
        {
            ft_putstr_fd("cd: ", STDOUT_FILENO);
            perror(token[1]);
            return (1);
        }
    }
    if (ret == 0)
        update_pwd(main);
    return (ret);
}