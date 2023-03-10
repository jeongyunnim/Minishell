/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/14 15:20:35 by jeseo            ###   ########.fr       */
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

int main(int argc, char *argv[], char *envp[])
{
	char	*input;
	int		stdio_fd[2];
	t_info	info;

	ft_memset(&info, 0, sizeof(info));
	info.envs = save_env(envp);
	info.envp_bash = envp;
	while (1)
	{
		info.pipes = 0;
		info.redirects = 0;
		input = readline("minishell$ ");
		if (input == NULL)
		{
			continue ;// 이자리는 엑싯임
		}
		add_history(input);
		parse(input, &info);
		if (args_check(&info) != ERROR && divide_pipe(&info) != ERROR)
		{
			//print_cmd_deque(&info);
			exec_commands(&info);
		}
		free(input);
		//free structs
	}
	return (0);
}
