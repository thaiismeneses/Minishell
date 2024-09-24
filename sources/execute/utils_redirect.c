/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:56:05 by thfranco          #+#    #+#             */
/*   Updated: 2024/08/27 15:13:48 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirect_and_cmd(char **cmd_splited, int i,
	char **new_cmd, char **redirect_and_file)
{
	if (cmd_splited[i][0] == '>' || cmd_splited[i][0] == '<')
	{
		if (cmd_splited[i + 1] != NULL)
		{
			*redirect_and_file = str_join(*redirect_and_file,
					cmd_splited[i]);
			*redirect_and_file = str_join(*redirect_and_file, " ");
			*redirect_and_file = str_join(*redirect_and_file,
					cmd_splited[i + 1]);
			i += 2;
			if (cmd_splited && cmd_splited[i] != NULL)
				*redirect_and_file = str_join(*redirect_and_file, " ");
		}
	}
	else if (cmd_splited[i][0] != '>' && cmd_splited[i][0] != '<')
	{
		*new_cmd = str_join(*new_cmd, cmd_splited[i]);
		*new_cmd = str_join(*new_cmd, " ");
		i++;
	}
	return (i);
}

char	*reorganize_redirect(char *cmd)
{
	char	*new_cmd;
	char	**cmd_splited;
	char	*redirect_and_file;
	int		i;

	i = 0;
	new_cmd = NULL;
	redirect_and_file = NULL;
	cmd_splited = new_split(cmd);
	while (cmd_splited[i] != NULL)
	{
		i = handle_redirect_and_cmd(cmd_splited, i,
				&new_cmd, &redirect_and_file);
	}
	ft_free_tab(cmd_splited);
	new_cmd = str_join(new_cmd, redirect_and_file);
	free(redirect_and_file);
	return (new_cmd);
}

char	*before_redirect(char *value)
{
	char	*before;
	int		i;

	i = 0;
	if (value[0] == '<' || value[0] == '>')
	{
		before = NULL;
		return (before);
	}
	before = malloc(sizeof(char) * ft_strlen(value));
	if (!before)
		return (NULL);
	while (value[i] != '<' && value[i] != '>' && value[i] != '\0')
	{
		before[i] = value[i];
		i++;
	}
	before[i] = '\0';
	return (before);
}

char	*after_redirect(char *value, int *i)
{
	char	*after;
	int		j;
	int		size;
	int		init;

	init = *i;
	size = init;
	j = 0;
	if ((value[size] == '>' || value[size] == '<'))
		size++;
	while (value[size] != '\0' && isblank(value[size]))
		size++;
	init = size;
	while (value[size] != '\0' && !isblank(value[size]))
		size++;
	after = malloc(sizeof(char) * (size - init + 1));
	if (!after)
		return (NULL);
	while (value[init] != '\0' && init < size)
	{
		after[j++] = value[init++];
	}
	after[j++] = '\0';
	*i = size;
	return (after);
}

int	handle_input_redirect(char *value, int i, int *fd_in)
{
	char	*infile;

	i++;
	infile = after_redirect(value, &i);
	if (*fd_in != 0)
		close(*fd_in);
	if (access(infile, F_OK | R_OK) == 0)
	{
		if (*fd_in != 0)
			close(*fd_in);
		*fd_in = open(infile, O_RDONLY);
	}
	else
	{
		*fd_in = 0;
		print_error_exc("No such file or directory", &infile);
		return (-1);
	}
	free(infile);
	return (i);
}
