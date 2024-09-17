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

void	display_file_content(void)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	fd = open("heredoc", O_RDONLY);
	if (fd < 0)
	{
		print_error("heredoc: ", strerror(errno));
		exit(1);
	}
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(1, buffer, bytes_read);
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
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

int	heredoc(char *target)
{
	int	fd;

	fd = create_temp_file();
	while (target != NULL)
	{
			heredoc_aux(target, fd);
	}
	// close(fd);
	// display_file_content();
	// unlink("heredoc");
	return (fd);
}
