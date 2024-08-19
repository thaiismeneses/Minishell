#include "../../includes/minishell.h"

void    handle_sigint(int sig)
{
    if (sig == SIGINT)
    {
		if (RL_ISSTATE(RL_STATE_READCMD))
		{
			if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			{
				perror("ioctl");
				return ;
			}
		}
		else
		{
			if (write(STDIN_FILENO, "\n", 1) == -1)
			{
				perror("write");
				return ;
			}
		}
		rl_replace_line("", 1);
		rl_on_new_line();
		g_status = 130;
	}
	return ;
}

void    mini_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
