/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 15:18:13 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	after_exec_commands(t_info *info, char **input)
{
	if (is_only_white_space(*input) == 0)
		add_history(*input);
	free(*input);
	preserve_stdio(1);
	reset_input_mode(&info->org_term);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_info	info;

	ft_putstr_fd("--- wellcome! ---\n", 1);
	init_info(&info, envp);
	while (1)
	{
		ready_for_input(&info);
		input = readline("minishell$ ");
		if (input == NULL)
			meet_eof_exit();
		if (parse(input, &info) < 0)
		{
			ft_putstr_fd("minishell: syntax error quote is not closed\n", 2);
			continue ;
		}
		if (args_check(&info) != ERROR && divide_pipe(&info) == 0)
			exec_commands(&info);
		else
			free_arg_deque(&info.arguments);
		after_exec_commands(&info, &input);
	}
	return (0);
}
