/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:48:38 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/04 19:48:38 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env_nodes(t_env_node *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

char	**allocate_env_array(int count)
{
	char	**env_array;

	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	env_array[count] = NULL;
	return (env_array);
}

char	**convert_to_array(t_env_node *env_list)
{
	int			count;
	int			i;
	char		**env_array;
	t_env_node	*temp;

	i = 0;
	count = count_env_nodes(env_list);
	env_array = allocate_env_array(count);
	if (!env_array)
		return (NULL);
	temp = env_list;
	while (i < count)
	{
		env_array[i] = strdup(temp->line_env);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		temp = temp->next;
		i++;
	}
	return (env_array);
}

char	*my_env(char *find, t_env_node *env_list)
{
	t_env_node	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name_env, find) == 0)
			return (temp->value_env);
		temp = temp->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env_node *env_list)
{
	int		i;
	char	*path;
	char	**paths;
	char	*part_path;
	char	*env;

	env = my_env("PATH", env_list);
	if (!env)
		return (ft_strdup(cmd));
	paths = ft_split(env, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		free(path);
	}
	ft_free_tab(paths);
	return (ft_strdup(cmd));
}
