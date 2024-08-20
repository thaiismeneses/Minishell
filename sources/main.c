/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:49 by penascim          #+#    #+#             */
/*   Updated: 2024/08/17 14:32:21 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	g_status;
extern char	**environ;

static void	run(char *prompt, t_main *main)
{
	char	*cmd;
	t_token	*tokens;

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
				exec_cmd(main);
			}
			free_list(&tokens);
		}
		free(cmd);
	}
	rl_clear_history();
}

void	print_prompt(t_main *main)
{
	char	*prompt;

	prompt = "minishell$ ";
	run(prompt, main);
}
static t_main *build_main(t_main *main)
{
	(void) main;
	char **envp = environ;
	t_main	*new_main;

	new_main = malloc(sizeof(t_main));
	if (!new_main)
		exit (1);
	new_main->env = build_environ(envp);
	new_main->token = NULL;
	start_pwd(new_main);
	return (new_main);
}

int	main(void)
{
	g_status = 0;
	t_main	*main;

	main = NULL;
	mini_signal();
	main = build_main(main);
	print_prompt(main);
	return (0);
}
