/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:48:12 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:48:12 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exec_error(char **cmd, t_main *main)
{
	print_error_exc("command not found", cmd);
	if (main)
		free_main(main);
	if (cmd)
		ft_free_tab(cmd);
	cmd = NULL;
	exit(127);
}

void	execute_child_process(char *path, char **cmd,
	t_env_node *env_list, t_main *main)
{
	char	**env_array;

	signal(SIGQUIT, SIG_DFL);
	env_array = convert_to_array(env_list);
	if (execve(path, cmd, env_array) == -1)
	{
		if (path)
			free(path);
		if (env_array)
			ft_free_tab(env_array);
		handle_exec_error(cmd, main);
	}
	if (main)
		free_main(main);
}

void	execute_command(char *path, char **cmd,
	t_env_node *env_list, t_main *main)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("fork error.\n", 2);
	else if (pid == 0)
		execute_child_process(path, cmd, env_list, main);
	else
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) == 0
			&& (!ft_strcmp(cmd[0], "cat") || !ft_strcmp(cmd[0], "grep")))
			status = 130;
		if (status == 139)
			status = 1;
		last_status(status);
	}
}

void	ft_execute(char *av, t_env_node *env_list, t_main *main)
{
	char	**cmd;
	char	*path;

	cmd = new_split(av);
	if (cmd[0] == NULL)
		path = cmd[0];
	else
		path = get_path(cmd[0], env_list);
	if (path == NULL)
	{
		print_error_exc("command does not exist: ", cmd);
		if (cmd)
			ft_free_tab(cmd);
		cmd = NULL;
		return ;
	}
	else if (!builtins(cmd, path, main))
		execute_command(path, cmd, env_list, main);
	if (cmd)
		ft_free_tab(cmd);
	cmd = NULL;
	if (path)
		free(path);
	path = NULL;
}

int	execute(t_tree_node *node, t_main *main, int flag)
{
	t_tree_node	*new_node;

	new_node = node;
	if (new_node == NULL)
		return (0);
	if (new_node->type == CMD)
		ft_execute(new_node->value, main->env, main);
	if (new_node->type == COMMAND_SUBSTITUTION)
		execute_redirects(new_node, main);
	else if (new_node->type == PIPE)
		execute_pipe(new_node, main);
	if (flag == 1)
	{
		if (main->token)
		{
			free_list(&main->token);
			main->token = NULL;
		}
		if (main->tree)
		{
			free_tree(main->tree);
			main->tree = NULL;
		}
	}
	return (0);
}
