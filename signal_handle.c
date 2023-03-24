/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:03:07 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 14:35:32 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler_interactive_mode(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_code = 130;
	}
}

static void	heredoc_sigint_handler(int signo)
{
	static int	signal_flag;

	if (signo == SIGINT)
		signal_flag = 1;
	else
		signal_flag = 0;
}

void	exited_by_signal(t_info *info, int signal)
{
	info->exit_code = signal + 128;
	if (signal == 15)
		ft_putstr_fd("Terminated: 15\n", 1);
	else if (signal == 2)
		ft_putstr_fd("\n", 1);
	else if (signal == 3)
		ft_putstr_fd("Quit: 3\n", 1);
	else if (signal == 15)
		ft_putstr_fd("Killed: 9\n", 1);
	else
	{
		ft_putstr_fd("Process got signal stop: ", 1);
		ft_putstr_fd(ft_itoa(signal), 1);
		ft_putstr_fd("\n", 1);
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
