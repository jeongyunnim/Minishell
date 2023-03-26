/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 18:35:53 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_info	info;

	print_openningment();
	init_info(&info, envp, argc, argv);
	while (1)
	{
		ready_for_input(&info);
		input = readline("minishell$ ");
		if (input == NULL)
			meet_eof_exit();
		if (is_only_white_space(input) == 0)
			add_history(input);
		if (parse(input, &info) < 0)
		{
			quote_error(&info, &input);
			continue ;
		}
		if (args_check(&info) != ERROR && divide_pipe(&info) == 0)
			exec_commands(&info);
		else
			free_arg_deque(&info.arguments);
		after_exec_commands(&input);
	}
	return (0);
}
