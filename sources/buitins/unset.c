#include "../../includes/minishell.h"

void remove_node_unset(char *token, t_main *main)
{
    t_env_node *temp;
    t_env_node *prev;

    temp = main->env;
    prev = NULL;
    while (temp != NULL)
    {
        if (!ft_strcmp(token, temp->name_env))
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

int ft_unset(char **token, t_main *main)
{
    int i;

    i = 1;
    while(token[i])
    {
        remove_node_unset(token[i], main);
        i++;
    }
    return (0);
}