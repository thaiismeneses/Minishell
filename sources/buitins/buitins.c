/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:05 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:33:12 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void    remove_quotes(t_token *data)
{
    int     i;
    int     j;
    char    quote;
    char    *string_quote;
    t_token *temp;

    i = 0;
    j = 0;
    temp = data;
    while (temp)
    {
        while(temp->value[i])
        {
            if (temp->value[i] == "\'" || temp->value[i] == "\"")
            {
                j = i + 1;
                quote = temp->value[i];
                while (temp->value[j] != '\0' && temp->value[j] != quote)
                    j++;
                if(temp->value[j] == quote)
                {
                    string_quote = ft_calloc(sizeof(char), ft_strlen(temp->value) - 1)
                    free(temp->value);
                    temp->value = string_quote;
                }
            }
            i++;
        }
        temp = temp->next;
    }
}

/*char *remove_quotes_from_string(const char *str) {
    size_t len = strlen(str);
    char *new_str = malloc(len + 1); // Aloca memória para a nova string
    if (!new_str) return NULL;

    size_t i = 0, j = 0;
    while (str[i]) {
        if (str[i] == '\'' || str[i] == '\"') {
            char quote = str[i];
            i++; // Pular o caractere de abertura da aspa

            // Copiar o conteúdo até a aspa de fechamento
            while (str[i] && str[i] != quote) {
                new_str[j++] = str[i++];
            }

            // Pular o caractere de fechamento da aspa
            if (str[i] == quote) {
                i++;
            }
        } else {
            new_str[j++] = str[i++];
        }
    }
    new_str[j] = '\0'; // Finalizar a string

    return new_str;
}

void remove_quotes(t_token *data) {
    t_token *temp = data;

    while (temp) {
        char *new_value = remove_quotes_from_string(temp->value);
        if (new_value) {
            free(temp->value);
            temp->value = new_value;
        }

        temp = temp->next;
    }
}*/

void    exec_cmd(t_main *main)
{
    t_token *temp;
    char	**matrix;

    temp = main->token;
    remove_quotes(main->token);
    while(temp)
	{
		matrix = ft_split(temp->value, ' ');
		builtins(matrix, main);
		temp = temp->next;
		free_matrix(matrix);
    }
}