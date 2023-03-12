/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 15:02:58 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	char	*input;
	int		stdio_fd[2];
	t_info	info;

	info.envs = save_env(env);
	while (1)
	{
		input = readline("Minishell$ ");
		if (input == NULL)
		{
			continue ;// 이자리는 엑싯임
		}
		add_history(input);
		parse(input, &info);
		if (print_args_deque(&info) != ERROR)
		{
			devide_pipe(&info);
			exec_commands(&info);
		}
		free(input);
		//free structs
	}
	return (0);
}
