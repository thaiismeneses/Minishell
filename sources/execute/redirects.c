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

void	execute_redirects(t_tree_node *node, t_main *main)
{
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (node->redir_info.fd_in != 0)
	{
		dup2(node->redir_info.fd_in, STDIN_FILENO);
		close(node->redir_info.fd_in);
	}
	if (node->redir_info.fd_out != 1)
	{
		dup2(node->redir_info.fd_out, STDOUT_FILENO);
		close(node->redir_info.fd_out);
	}
	if (node->redir_info.command)
		ft_execute(node->redir_info.command, main->env, main);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

int	handle_output_redirect(char *value, int i, int *fd_out)
{
	char	*outfile;

	outfile = after_redirect(value, &i);
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
		{
			print_error_exc("Permission denied", &outfile);
			free(outfile);
			return (-1);
		}
	}
	if (*fd_out != 1)
		close(*fd_out);
	*fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	free(outfile);
	return (i);
}

int	handle_output_append_redirect(char *value, int i, int *fd_out)
{
	char	*outfile;

	i += 2;
	outfile = after_redirect(value, &i);
	if (*fd_out != 1)
		close(*fd_out);
	*fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00777);
	free(outfile);
	return (i);
}

int	process_redirect(char *value, int i, t_redirect_info *redir_info)
{
	if (value[i] == '>' && value[i + 1] == '>')
		i = handle_output_append_redirect(value, i, &(redir_info->fd_out));
	else if (value[i] == '>')
	{
		i = handle_output_redirect(value, i, &(redir_info->fd_out));
		if (i == -1)
			return (-1);
	}
	else if (value[i] == '<' && value[i + 1] == '<')
		i = handle_heredoc_redirect(value, i, redir_info);
	else if (value[i] == '<')
	{
		i = handle_input_redirect(value, i, &(redir_info->fd_in));
		if (i == -1)
			return (-1);
	}
	if (value[i] != '\0')
		i++;
	return (i);
}

int	handle_redirect(t_tree_node *node, t_main *main)
{
	t_redirect_info	redir_info;
	char			*value;
	int				i;

	redir_info = init_handle_redirect(node);
	value = reorganize_redirect(ft_strdup(node->value));
	i = 0;
	while (value[i] != '\0')
	{
		i = process_redirect(value, i, &redir_info);
		if (i < 0)
		{
			free(redir_info.command);
			free(value);
			free_tree(main->tree);
			free_list(&main->token);
			return (-1);
		}
	}
	free(value);
	node->redir_info = redir_info;
	return (i);
}
