/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:40:43 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/22 18:14:20 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	redirect_in(void)
{
	int	fd;

	fd = open()
}*/
int is_redirection_operator(char *str) {
    return (strcmp(str, ">") == 0 || strcmp(str, ">>") == 0 || strcmp(str, "<") == 0);
}

void	handle_redirections(t_tree_node * node)
{
	int	fd;
	char **value;
	int	i;


	value = ft_split(node->value, ' ');
	i = 0;
	// printf("AQUIII\n");
	printf("VALUE TOKEN[0]: %s\n", value[0]);
	while (value[i] != NULL)
	{
		if (ft_strcmp(value[i],">")) // ">"
		{
			fd = open(value[i++], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
			close(fd);
		}
		else if (ft_strcmp(value[i], ">>")) // ">>"
		{
			fd = open(value[i++], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
			close(fd);
		}
		else if (ft_strcmp(value[i],"<")) // "<"
		{
			fd = open(value[i++], O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDIN_FILENO); // Redireciona stdin para o arquivo
			close(fd);
		}
		i++;
	}
}


void execute_command_with_redirection(t_tree_node *node)
{
    char **tokens;
    int i = 0;
    int j = 0;
    char *command[256]; // Para armazenar o comando principal

    tokens = ft_split(node->value, ' ');

    // Separar o comando principal dos operadores de redirecionamento
    while (tokens[i] != NULL)
    {
        if (is_redirection_operator(tokens[i]))
            break;
        command[j++] = tokens[i];
        i++;
    }
    command[j] = NULL; // Termina a lista de argumentos do comando principal

    // Tratar redirecionamentos
    handle_redirections(node);

    // Executar o comando principal
    if (fork() == 0) // Processo filho para executar o comando
    {
        execvp(command[0], command); // Executa o comando com seus argumentos
        perror("execvp"); // Se execvp falhar
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL); // Espera o processo filho terminar
    }

    // Liberar a memória alocada por ft_split, se necessário
}

