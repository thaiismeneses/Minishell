/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:17:51 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/15 18:33:20 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **convert_to_array(t_env_node *env_list) 
{
    int count;
	t_env_node *temp;

	count = 0;
	temp = env_list;
    // Contando quantas variáveis de ambiente existem na lista
    while (temp) {
        count++;
        temp = temp->next;
    }

    // Alocando espaço para o array de strings (+1 para o NULL final)
    char **env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;

    // Copiando as variáveis para o array
    temp = env_list;
    for (int i = 0; i < count; i++) {
        env_array[i] = strdup(temp->line_env); // `line_env` já deve ter o formato "NOME=VALOR"
        if (!env_array[i]) {
            // Liberação de memória em caso de erro
            while (i > 0)
                free(env_array[--i]);
            free(env_array);
            return NULL;
        }
        temp = temp->next;
    }

    // Definindo o último elemento como NULL
    env_array[count] = NULL;

    return env_array;
}

char	*my_env(char *find, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, find) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_path(char *cmd)
{
	int		i;
	char	*path;
	char	**paths;
	char	*part_path;
	char	**s_cmd;

	paths = ft_split(getenv("PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, s_cmd[0]);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		else
			free(path);
	}
	ft_free_tab(paths);
	ft_free_tab(s_cmd);
	return (cmd);
}

void	print_error_exc(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (errno != 0)
		perror("");
	exit(1);
}

void	ft_execute(char *av, t_env_node *env_list)
{
	char	**cmd;
	char	*path;
	printf("AQUII\n");
	printf("value: %s\n", av);
	cmd = ft_split(av, ' ');
	path = get_path(cmd[0]);
	if (path == NULL)
	{
		ft_putstr_fd(cmd[0], 2);
		print_error_exc("command does not exits.\n");
		ft_free_tab(cmd);
	}
	if (execve(path, cmd, convert_to_array(env_list)) == -1)
	{
		ft_putstr_fd(cmd[0], 2);
		print_error_exc("command not found.\n");
		ft_free_tab(cmd);
		free(path);
	}
}

void	execute_pipe(t_tree_node *node, t_main *main)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
		print_error_exc("pipe error.\n");
	if ((pid1 = fork()) == -1)
		print_error_exc("fork error.\n");
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_cmd(node, main);
		exit(EXIT_SUCCESS);
	}
	if ((pid2 = fork()) == -1)
		print_error_exc("fork error.\n");
	if (pid2 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_cmd(node, main);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	execute_cmd(t_tree_node *node, t_main *main)
{
	if (node == NULL)
		return (-1);
	print_env_list(main->env_list);
	if (node->type == CMD)
		ft_execute(node->value, main->env_list);
	else if (node->type == PIPE)
	{
		execute_pipe(node->left, main);
	}
	return (0);
}