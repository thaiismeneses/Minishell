/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:49 by penascim          #+#    #+#             */
/*   Updated: 2024/08/15 19:08:35 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;




static void	run(char *prompt)
{
	char	*cmd;
	t_token	*tokens;
	t_main	*main;

	main = NULL;
	tokens = NULL;
	char **envp = environ;
	main->env_list = build_environ(envp);
	//mini_signal();
	while (42)
	{
		cmd = readline(prompt);
		if (!cmd)
			cmd = ft_strdup("exit");
		if (*cmd)
		{
			add_history(cmd);
			tokens = tokenization(cmd, tokens);
			//print_token_list(tokens);
			if (has_error(tokens))
			{
				check_values(tokens, main);
				heredoc(tokens);
			}
			free_list(&tokens);
		}
		free(cmd);
	}
	rl_clear_history();
}

void	print_prompt(void)
{
	char	*prompt;

	prompt = "minishell$ ";
	run(prompt);
}

int	main(void)
{
	
   
	print_prompt();
	return (0);
}
