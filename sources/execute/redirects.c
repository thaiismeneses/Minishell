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


void	execute_redirects(int fd_in, int fd_out, char *cmd, t_main *main)
{
	int save_in;
	int save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (cmd)
		ft_execute(cmd, main->env, main);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

char *reorganize_redirect(char *cmd)
{
	char *new_cmd;
	char **cmd_splited;
	char *redirect_and_file;
	int i;

	i = 0;
	new_cmd = NULL;
	redirect_and_file = NULL;
	printf("CMD: %s\n", cmd);
	cmd_splited = new_split(cmd);
	while (cmd_splited[i])
	{
		printf("%s\n", cmd_splited[i++]);
	}
	i = 0;
	while (cmd_splited[i] != NULL)
	{
		if (cmd_splited [i][0] == '>' || cmd_splited[i][0] == '<')
		{
			if (cmd_splited[i + 1] != NULL)
			{
				redirect_and_file = str_join(redirect_and_file, cmd_splited[i]);
				redirect_and_file = str_join(redirect_and_file, " ");
				redirect_and_file = str_join(redirect_and_file, cmd_splited[i + 1]);
				i += 2;
				if (cmd_splited && cmd_splited[i] != NULL)
					redirect_and_file = str_join(redirect_and_file, " ");
			}
		}
		else if (cmd_splited[i][0] != '>' || cmd_splited[i][0] != '<')
		{
			new_cmd = str_join(new_cmd, cmd_splited[i]);
			new_cmd = str_join(new_cmd, " ");
			i++;
		}
	}
	ft_free_tab(cmd_splited);
	new_cmd = str_join(new_cmd, redirect_and_file);
	free (redirect_and_file);
	return(new_cmd);
}

void	handle_redirect(t_tree_node *node, t_main *main)
{
	t_tree_node *new_node;
	char	*value;
	char *comando;
	int		i;
	int	fd_in;
	int fd_out;
	char *outfile;
	char *infile;
	int heredoc_fd;
	char *cmd;

	i = 0;
	outfile = NULL;
	infile = NULL;
	new_node = node;
	cmd = ft_strdup(new_node->value);
	value = reorganize_redirect(cmd);
	free(cmd);
	comando = before_redirect(value);
	heredoc_fd = -1;
	fd_in = 0;
	fd_out = 1;
	while (value[i] != '\0')
	{
		if (value[i] == '>' && value[i + 1] == '>')
		{
			i += 2;
			outfile = after_redirect(value, &i);
			if (fd_out != 1)
				close(fd_out);
			fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00777);
		}
		else if (value[i] == '>')
		{
			i++;
			outfile = after_redirect(value, &i);
			if (fd_out != 1)
				close(fd_out);
			fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00777);
		}
		else if (value[i] == '<' && value[i + 1] == '<')
		{
			i += 2;
			infile = after_redirect(value, &i);
			printf("Infile: %s\n", infile);
			if (heredoc_fd != -1)
				close(heredoc_fd);
			heredoc_fd = create_temp_file();
			heredoc_aux(infile, heredoc_fd);
			close(heredoc_fd);
			if (fd_in != 0)
				close(fd_in);
			fd_in = open("heredoc", O_RDONLY);

		}
		else if (value[i] == '<')
		{
			i++;
			infile = after_redirect(value, &i);
			if (fd_in != 0)
					close (fd_in);
			if (access(infile, F_OK | R_OK) == 0)
			{
				if (fd_in != 0)
					close (fd_in);
				fd_in = open(infile, O_RDONLY);
			}
			else
			{
				fd_in = -1;
				print_error_exc("No such file or directory", &infile);
			}
		}
		if (value[i] != '\0')
			i++;
	}
	free(infile);
	free(outfile);
	free(value);
	if (fd_in != -1)
		execute_redirects(fd_in, fd_out, comando, main);
	free(comando);
	unlink("heredoc");
}
