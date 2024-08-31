/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:33:05 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/31 14:27:18 by thfranco         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	remove_quotes(t_main *main)
{
	int	i;
	char	quote;
	char	*temp;
	t_token	*data;
	t_token	*head;

	data = main->token;
	head = data;
	while (data)
	{
        if (!(ft_strcmp(data->value, "rm")) || !(ft_strcmp(data->value, "grep")) ||  !(ft_strcmp(data->value, "echo")))
        {
            while(data)
            {
                if (data->token == S_QUOTE || data->token == D_QUOTE)
                {
                    data->token = 0;
                    break ;
                }
                data = data->next;
            }
        }
		if (data->token == S_QUOTE || data->token == D_QUOTE)
		{
			quote = data->value[0];
			i = 1;
			while (data->value[i] != '\0')
			{
				if (data->value[i++] == quote)
					break ;
			}
			temp = ft_substr(data->value, 1, i - 2);
			if (temp)
			{
				free(data->value);
				data->value = ft_strdup(temp);
				data->token = 0;
				free(temp);
			}
		}
		data = data->next;
	}
	main->token = reorganize_cmd(head);
	free_list(&head);
}

//n sei se atualizo o valor de g_status msm
int	builtins(char **token, t_main *main)
{
	if (!token || !token[0])
		return (0);
	if (!ft_strcmp(token[0], "exit"))
		return (ft_exit(token), 1);
	if (!ft_strcmp(token[0], "env"))
		return (ft_env(token, main), 1);
	if (!ft_strcmp(token[0], "export"))
		return (ft_export(token, main), 1);
	if (!ft_strcmp(token[0], "unset"))
		return (ft_unset(token, main), 1);
	if (!ft_strcmp(token[0], "pwd"))
	{
		ft_putstr_fd(main->pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	if (!ft_strcmp(token[0], "cd"))
		return (ft_cd(token, main), 1);
	if (!ft_strcmp(token[0], "echo"))
		return (ft_echo(token), 1);
	return (0);
}
