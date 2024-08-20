/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:40:43 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/20 17:21:52 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	redirect_in(void)
{
	int	fd;

	fd = open()
}*/

void	handle_redirections(t_tree_node *node,t_main *main)
{
	int	fd;

	while (main->token)
	{
		if (main->token->token == REDIRECT_OUT) // ">"
		{
			fd = open(main->token->next, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
			close(fd);
		}
		else if (main->token->token == APPEND) // ">>"
		{
			fd = open(main->token->next, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDOUT_FILENO); // Redireciona stdout para o arquivo
			close(fd);
		}
		else if (main->token->token == REDIRECT_IN) // "<"
		{
			fd = open(main->token->next, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				return ;
			}
			dup2(fd, STDIN_FILENO); // Redireciona stdin para o arquivo
			close(fd);
		}
		main->token = main->token->next;
	}
}
