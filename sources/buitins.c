
#include "../includes/minishell.h"

/*int ft_env(char **token)
{
    (void) token;
    t_env_node *temp;

    temp = head;
    while (temp != NULL)
    {
        printf("Name: %s\nValue: %s\nLine: %s\n\n", temp->name_env, temp->value_env, temp->line_env);
        temp = temp->next;
    }
    return (0);
}*/

int builtins(char **token)
{
    if (!token || !token[0])
        return(0);
    if (!ft_strcmp(token[0], "exit"))
        g_status = ft_exit(token);
    /*if (!ft_strcmp(token[0], "env"))
        g_status = ft_env(token);*/
    return(0);
}
void    exec_cmd(t_main *main)
{
    char	**matrix;
    t_token *temp;

    temp = main->token;
    while(temp)
	{
		matrix = ft_split(temp->value, ' ');
		builtins(matrix);
		temp = temp->next;
		free(matrix);
	}
}
