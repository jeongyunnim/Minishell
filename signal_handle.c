#include "minishell.h"

void	signal_handler_interactive_mode(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	set_signal_mode(int flag)
{
	if (flag == INTERACTIVE_M)
	{
		signal(SIGINT, signal_handler_interactive_mode);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == FORK_CHILD_M)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (flag == FORK_PARENT_M)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else // heredoc
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}
