#include "../../includes/minishell.h"

int ft_env(char **token, t_main *main)
{
    t_env_node *temp;

    temp = main->env;
    if(token[1])
    {
        ft_putstr_fd("env: '", STDOUT_FILENO);
	    ft_putstr_fd(token[1], STDOUT_FILENO);
        ft_putstr_fd("': No such file or directory\n", STDOUT_FILENO);
        g_status = 130;
        return (1);
    }
    while (temp != NULL) 
    {
        ft_putstr_fd(temp->line_env, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        temp = temp->next;
    }
    return (0);
}