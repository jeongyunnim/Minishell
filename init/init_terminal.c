/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:20:27 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:21:06 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preserve_stdio(int flag)
{
	static int	stdio_fd[2];

	if (flag == 0)
	{
		stdio_fd[0] = dup(STDIN_FILENO);
		stdio_fd[1] = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(stdio_fd[0], 0);
		dup2(stdio_fd[1], 1);
		close(stdio_fd[0]);
		close(stdio_fd[1]);
	}
}

void	meet_eof_exit(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[11C", 1);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

void	ready_for_input(t_info *info)
{
	preserve_stdio(0);
	tcsetattr(STDIN_FILENO, TCSANOW, &info->new_term);
	set_signal_mode(INTERACTIVE_M);
	info->pipes = 0;
	info->redirects = 0;
}

void	after_exec_commands(char **input)
{
	free(*input);
	preserve_stdio(1);
}
