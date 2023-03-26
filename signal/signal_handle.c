/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:03:07 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:43:45 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler_interactive_mode(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	exited_by_signal(int signal)
{
	char	*temp;

	g_exit_code = signal + 128;
	if (signal == 15)
		ft_putstr_fd("Terminated: 15\n", 1);
	else if (signal == 2)
		ft_putstr_fd("\n", 1);
	else if (signal == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (signal == 9)
		ft_putstr_fd("Killed: 9\n", 1);
	else
	{
		temp = ft_itoa(signal);
		ft_putstr_fd("Process interupted by signal: ", 1);
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("\n", 1);
		free(temp);
	}
}

void	set_signal_mode(int flag)
{
	if (flag == INTERACTIVE_M)
	{
		signal(SIGINT, signal_handler_interactive_mode);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else if (flag == FORK_CHILD_M)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
	}
	else if (flag == FORK_PARENT_M)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
	}
}
