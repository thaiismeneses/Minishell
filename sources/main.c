/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:26:42 by thfranco          #+#    #+#             */
/*   Updated: 2024/09/18 13:47:21 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	run(char *prompt, t_main *main)
{
	char	*cmd;
	t_token	*tokens;

	last_status(0);
	while (42)
	{
		cmd = readline(prompt);
		if (!cmd)
			cmd = ft_strdup("exit");
		if (*cmd)
		{
			add_history(cmd);
			tokens = tokenization(cmd, tokens);
			if (has_error(tokens))
			{
				check_values(tokens, main);
				before_execute(main->tree);
				execute(main->tree, main, 1);
			}
		}
	}
	rl_clear_history();
}

void	print_prompt(t_main *main)
{
	char	*prompt;

	prompt = "minishell$ ";
	run(prompt, main);
}

static t_main	*build_main(t_main *main, char **envp)
{
	t_main	*new_main;

	(void) main;
	new_main = malloc(sizeof(t_main));
	if (!new_main)
		exit (1);
	new_main->env = build_environ(envp);
	new_main->token = NULL;
	new_main->tree = NULL;
	start_pwd(new_main);
	return (new_main);
}

int	main(int ac, char **av, char **envp)
{
	t_main	*main;

	(void) ac;
	(void) av;
	main = NULL;
	mini_signal();
	main = build_main(main, envp);
	print_prompt(main);
	return (0);
}
