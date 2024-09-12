/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:34:38 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/08/22 09:34:42 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	err_signal(char *err)
{
	perror(err);
	g_status = 1;
	last_status(130);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			{
				err_signal("ioctl");
				return ;
			}
		}
		else
		{
			if (write(STDIN_FILENO, "\n", 1) == -1)
			{
				err_signal("write");
				return ;
			}
		}
		last_status(130);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	return ;
}

void	mini_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}