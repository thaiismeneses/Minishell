/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:36:09 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/25 16:10:48 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		printf("pipe error.\n");
}

void	setup_child(int fd_in, int fd_out, t_tree_node *node, t_main *main)
{
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execute(node, main);
	exit(EXIT_SUCCESS);
}

void	fork_and_exec(t_tree_node *node, t_main *main, int pipe_fd[2])
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		printf("fork error.\n");
	if (pid1 == 0)
		setup_child(pipe_fd[0], pipe_fd[1], node->left, main);
	pid2 = fork();
	if (pid2 == -1)
		printf("fork error.\n");
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execute(node->right, main);
		exit(EXIT_SUCCESS);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	execute_pipe(t_tree_node *node, t_main *main)
{
	int	pipe_fd[2];

	setup_pipe(pipe_fd);
	fork_and_exec(node, main, pipe_fd);
}
