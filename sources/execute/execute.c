/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:17:51 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/23 12:01:59 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**convert_to_array(t_env_node *env_list)
{
	int			count;
	t_env_node	*temp;
	char		**env_array;
	int			i;

	count = 0;
	temp = env_list;
	i = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	temp = env_list;
	while (i < count)
	{
		env_array[i] = strdup(temp->line_env);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

char	*my_env(char *find, t_env_node *env_list)
{
	t_env_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name_env, find) == 0)
			return (temp->value_env);
		temp = temp->next;
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

char	*get_path(char *cmd, t_env_node *env_list)
{
	int		i;
	char	*path;
	char	**paths;
	char	*part_path;

	paths = ft_split(my_env("PATH", env_list), ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		else
			free(path);
	}
	// ft_free_tab(paths);
	return (cmd);
}

void	print_error_exc(char *msg, char *cmd)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	// if (errno != 0)
	// 	perror("");
	// exit(1);
}

void	ft_execute(char *av, t_env_node *env_list)
{
	char	**cmd;
	char	*path;
	pid_t	pid;

	cmd = ft_split(av, ' ');
	path = get_path(cmd[0], env_list);
	if (path == NULL)
	{
		print_error_exc("command does not exits: ", cmd[0]);
		ft_free_tab(cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
		printf("fork error.\n");
	else if (pid == 0)
	{

		if (execve(path, cmd, convert_to_array(env_list)) == -1)
		{
			print_error_exc("command not found: ", cmd[0]);
			ft_free_tab(cmd);
			// free(path);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		ft_free_tab(cmd);
		// free(path);
	}
}

void	execute_pipe(t_tree_node *node, t_main *main)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	//printf("pipe\n");
	if (pipe(pipe_fd) == -1)
		printf("pipe error.\n");
	if ((pid1 = fork()) == -1)
		printf("fork error.\n");
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execute_cmd(node->left, main);
		exit(EXIT_SUCCESS);
	}
	if ((pid2 = fork()) == -1)
		printf("fork error.\n");
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execute_cmd(node->right, main);
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
		return (0);
	if (node->type == CMD)
		ft_execute(node->value, main->env);
	if (node->type == COMMAND_SUBSTITUTION)
	{
		handle_redirect(node);
	}
	else if (node->type == PIPE)
	{
		execute_pipe(node, main);
	}
	return (0);
}
