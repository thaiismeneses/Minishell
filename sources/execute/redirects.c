/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:40:43 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/23 13:29:53 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_output_redirect(char *value, char *output_file, t_main *main)
{
	int	fd_out;
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("Error to open file");
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_execute(value, main->env, main);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
}

void	handle_input_redirect(char *value, char *input_file, t_main *main)
{
	int	fd_in;
	int	save_stdin;

	save_stdin = dup(STDOUT_FILENO);
	fd_in = open(input_file, O_RDONLY);
	if (fd_in < 0)
	{
		perror("Error to open file input");
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	ft_execute(value, main->env, main);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
}

void	handle_append_redirect(char *value, char *output_file, t_main *main)
{
	int	fd_out;
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		perror("Error to open file");
		exit(1);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	ft_execute(value, main->env, main);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
}

void	handle_redirect(t_tree_node *node, t_main *main)
{
	char	*value;
	char	*redirect;
	char	*file_name;

	redirect = find_redirect(node->value);
	value = before_redirect(node->value);
	file_name = after_redirect(node->value);
	if (redirect[0] == '>')
	{
		if (redirect[1] == '>')
			handle_append_redirect(value, file_name, main);
		else
			handle_output_redirect(value, file_name, main);
	}
	else if (redirect[0] == '<')
	{
		if (redirect[1] == '<')
			heredoc(main->token);
		else
			handle_input_redirect(value, file_name, main);
	}

}
