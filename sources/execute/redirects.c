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

// void	handle_output_redirect(char *value, char *output_file, t_main *main)
// {
// 	int	fd_out;
// 	int	save_stdout;

// 	save_stdout = dup(STDOUT_FILENO);
// 	fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd_out < 0)
// 	{
// 		perror("Error to open file");
// 		exit(1);
// 	}
// 	dup2(fd_out, STDOUT_FILENO);
// 	close(fd_out);
// 	ft_execute(value, main->env, main);
// 	dup2(save_stdout, STDOUT_FILENO);
// 	close(save_stdout);
// }

// void	handle_input_redirect(char *value, char *input_file, t_main *main)
// {
// 	int	fd_in;
// 	int	save_stdin;

// 	save_stdin = dup(STDOUT_FILENO);
// 	fd_in = open(input_file, O_RDONLY);
// 	if (fd_in < 0)
// 	{
// 		perror("Error to open file input");
// 		exit(1);
// 	}
// 	dup2(fd_in, STDIN_FILENO);
// 	close(fd_in);
// 	ft_execute(value, main->env, main);
// 	dup2(save_stdin, STDIN_FILENO);
// 	close(save_stdin);
// }

// void	handle_append_redirect(char *value, char *output_file, t_main *main)
// {
// 	int	fd_out;
// 	int	save_stdout;

// 	save_stdout = dup(STDOUT_FILENO);
// 	fd_out = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (fd_out < 0)
// 	{
// 		perror("Error to open file");
// 		exit(1);
// 	}
// 	dup2(fd_out, STDOUT_FILENO);
// 	close(fd_out);
// 	ft_execute(value, main->env, main);
// 	dup2(save_stdout, STDOUT_FILENO);
// 	close(save_stdout);
// }

void	handle_redirect(t_tree_node *node, t_main *main)
{
	char	*value;
	int		i;
	int	fd_in;
	int fd_out;
	char *outfile;
	char *infile;
	(void)main;

	i = 0;
	outfile = NULL;
	infile = NULL;
	value = ft_strdup(node->value);
	printf("STRING: %s\n", value);
	fd_in = 0;
	fd_out = 1;
	while (value[i] != '\0')
	{
		if (value[i] == '>')
		{
			i++;
			if (value[i] == '>')
			{
				i++;
				printf("ANTES REDIRECT i: %d\n", i);
				outfile = after_redirect(value, &i);
				printf("DEPOIS REDIRECT i: %d\n", i);
				printf ("OUTFILE: %s\n", outfile);
				if (fd_out != 1)
					close(fd_out);
				fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
				printf("FD_OUT APPEND: %d\n", fd_out);

			}
			else
			{
				outfile = after_redirect(value, &i);
				printf ("OUTFILE: %s\n", outfile);
				if (fd_out != 1)
					close(fd_out);
				fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				printf("FD_OUT: %d\n", fd_out);

			}
		}
		else if (value[i] == '<')
		{
			i++;
			if (value[i] == '<')
			{
				i++;
				infile = after_redirect(value, &i);
				printf ("OUTFILE: %s\n", infile);
				if (fd_in != 1)
					close(fd_in);
				//heredoc
			}
			else
			{
				if (fd_in != 0)
					close(fd_in);
				fd_in = open(infile, O_RDONLY);
				printf("FD_IN: %d\n", fd_in);
			}
		}
		else
		{
			printf("i: %d\n", i);
			i++;
		}
	}
	// free(value);
	// free(file_name);
	//free(redirect);
}
