/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 21:18:40 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_deque(t_info *info)
{
	t_cmd	*temp_cmd;
	t_arg	*temp;
	int		i;
	int		j;

	i = 0;
	temp_cmd = info->cmds->head;
	while (temp_cmd != NULL)
	{
		printf("\n---------------- < %d번째 command line >----------------\n\n", i);
		if (temp_cmd->redirections != NULL)
		{
			temp = temp_cmd->redirections->head;
			while (temp != NULL)
			{
				printf("type:%d | file: %s \n", temp->special, temp->arg);
				temp = temp->next;
			}
		}
		j = 0;
		while (temp_cmd->commands_args[j] != NULL)
		{
			printf("arg[%d]: %s\n", j, temp_cmd->commands_args[j]);
			j++;
		}
		printf("\n--------------------------------------------------------\n");
		temp_cmd = temp_cmd->next;
		i++;
	}
}

int main(int argc, char *argv[], char *env[])
{
	char	*input;
	int		stdio_fd[2];
	t_info	info;

	info.envs = save_env(env);
	info.envp_bash = env;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			continue ;// 이자리는 엑싯임
		}
		add_history(input);
		parse(input, &info);
		if (print_args_deque(&info) != ERROR && devide_pipe(&info) != ERROR)
		{
			print_cmd_deque(&info);
			exec_commands(&info);
		}
		free(input);
		//free structs
	}
	print_args_deque(&info);
	return (0);
}
