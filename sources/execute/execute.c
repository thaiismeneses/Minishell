/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:17:51 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/30 16:24:38 by thfranco         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	handle_exec_error(char **cmd)
{
	print_error_exc("command not found: ", cmd[0]);
	ft_free_tab(cmd);
	exit(127);
}

void	execute_child_process(char *path, char **cmd, t_env_node *env_list)
{
	if (execve(path, cmd, convert_to_array(env_list)) == -1)
		handle_exec_error(cmd);
}

void	execute_command(char *path, char **cmd, t_env_node *env_list)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("fork error.\n");
	else if (pid == 0)
		execute_child_process(path, cmd, env_list);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 139)
			status = 1;
		if ((!ft_strcmp(cmd[0], "cat") || !ft_strcmp(cmd[0], "grep")) && status == 4)
			status = 130;
		last_status(status);
		ft_free_tab(cmd);
	}
}

void	ft_execute(char *av, t_env_node *env_list, t_main *main)
{
	char	**cmd;
	char	*path;

	cmd = new_split(av);
	path = get_path(cmd[0], env_list);
	if (path == NULL)
	{
		print_error_exc("command does not exist: ", cmd[0]);
		ft_free_tab(cmd);
		return ;
	}
	if (!builtins(cmd, main))
		execute_command(path, cmd, env_list);
}

int	execute(t_tree_node *node, t_main *main)
{
	if (node == NULL)
		return (0);
	if (node->type == CMD)
		ft_execute(node->value, main->env, main);
	if (node->type == COMMAND_SUBSTITUTION)
	{
		handle_redirect(node, main);
	}
	else if (node->type == PIPE)
	{
		execute_pipe(node, main);
	}
	return (0);
}