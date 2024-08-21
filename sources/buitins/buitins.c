#include "../../includes/minishell.h"

//n sei se atualizo o valor de g_status msm
int builtins(char **token, t_main *main)
{
    if (!token || !token[0])
        return(0);
    if (!ft_strcmp(token[0], "exit"))
        g_status = ft_exit(token);
    if (!ft_strcmp(token[0], "env"))
        g_status = ft_env(token, main);
    if (!ft_strcmp(token[0], "export"))
        g_status = ft_export(token, main);
    if (!ft_strcmp(token[0], "unset"))
        g_status = ft_unset(token, main);
    if (!ft_strcmp(token[0], "pwd"))
    {
        ft_putstr_fd(main->pwd, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
    if (!ft_strcmp(token[0], "cd"))
        g_status = ft_cd(token, main);
    if (!ft_strcmp(token[0], "echo"))
        g_status = ft_echo(token);
    return(0);
}
void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
	matrix = NULL;
}

void    exec_cmd(t_main *main)
{
    char	**matrix;

    while(main->token)
	{
		matrix = ft_split(main->token->value, ' ');
		builtins(matrix, main);
		main->token = main->token->next;
		free_matrix(matrix);
	}
}