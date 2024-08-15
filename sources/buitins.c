#include "../includes/minishell.h"

int	error_exit(char *token, int option)
{
    ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (option == 1)
	{
        (void)token;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
        return (1);
	}
	else
	{
        ft_putstr_fd("minishell: ", STDOUT_FILENO);
        ft_putstr_fd(token, STDOUT_FILENO);
        ft_putstr_fd(" : numeric argument required\n", STDOUT_FILENO);
        return (2);
	}
}

int is_number(char *token)
{
    int i;
    //long long    result;

    i = 0;
    if (token[i] == '-' || token[i] == '+')
        i++;
    if (token[i] == '\0')
        return (0);
    while (token[i])
    {
        if (!ft_isdigit(token[i]))
            return 0;
        i++;
    }
    //result = ft_atoll(token);
    //printf("Resultado: %lld", result);
    //if (result > LONG_MAX || result < LONG_MIN)
        //return 0;
    return (1);
}

int    ft_exit(char **token)
{
    int exit_code;

    exit_code = 0;
    if(token[1] && token[2])
        return(error_exit(token[1], 1));
    else if (token[1] && !is_number(token[1]))
    {
        error_exit(token[1], 2);
        exit(2);
    }
    else
    {
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        if (token[1])
            exit_code = ft_atol(token[1]);
        exit(exit_code);
    }
}

int builtins(char **token)
{
    if (!token || !token[0])
        return(0);
    if (!ft_strcmp(token[0], "exit"))
        g_status = ft_exit(token); //pensar em como fazer isso!!!!!
    return(0);
}