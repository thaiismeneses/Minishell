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

int	create_temp_file(void)
{
	int		fd;
	char	*file;

	file = "heredoc";
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
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

int	handle_heredoc_redirect(char *value, int i, int *fd_in, int *heredoc_fd)
{
	char	*infile;

	i += 2;
	infile = after_redirect(value, &i);
	printf("Infile: %s\n", infile);
	if (*heredoc_fd != -1)
		close(*heredoc_fd);
	*heredoc_fd = create_temp_file();
	heredoc_aux(infile, *heredoc_fd);
	close(*heredoc_fd);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = open("heredoc", O_RDONLY);
	free(infile);
	return (i);
}
