#include "../../includes/minishell.h"

int ft_env(t_main *main)
{
    t_env_node *temp;

    temp = main->env;
    while (temp != NULL) 
    {
        ft_putstr_fd(temp->line_env, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        temp = temp->next;
    }
    return (0);
}