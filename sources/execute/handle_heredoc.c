/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:30:55 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/17 15:19:52 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	before_execute(t_tree_node *node, t_main * main)
{
	t_tree_node	*temp;

	temp = node;
	if (temp && temp->type == COMMAND_SUBSTITUTION)
		return (handle_redirect(temp, main));
	if (temp && temp->left)
		before_execute(temp->left, main);
	if (temp && temp->right)
		before_execute(temp->right, main);
	return (0);
}

int	create_temp_file(char *infile)
{
	int		fd;

	fd = open(infile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error("heredoc: ", strerror(errno));
		exit(1);
	}
	return (fd);
}

void	heredoc_aux(char *target, int fd)
{
	char	*line;

	while (42)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			last_status(0);
			break ;
		}
		if (!target)
			break ;
		if (!ft_strncmp(line, target, ft_strlen(target))
			&& ft_strlen(line) == ft_strlen(target))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close (fd);
}

int	handle_heredoc_redirect(char *value, int i, t_redirect_info *redir_info)
{
	char	*infile;

	i += 2;
	infile = after_redirect(value, &i);
	if (redir_info->heredoc_fd != -1)
		close(redir_info->heredoc_fd);
	redir_info->heredoc_fd = create_temp_file(infile);
	heredoc_aux(infile, redir_info->heredoc_fd);
	close(redir_info->heredoc_fd);
	if (redir_info->fd_in != 0)
		close(redir_info->fd_in);
	redir_info->fd_in = open(infile, O_RDONLY);
	redir_info->file = ft_strdup(infile);
	free(infile);
	return (i);
}
