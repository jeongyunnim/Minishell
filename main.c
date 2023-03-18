/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/18 17:56:25 by jeseo            ###   ########.fr       */
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

/* 터미널 모드 설정 */

void	save_input_mode(struct termios *org_term)
{
	tcgetattr(STDIN_FILENO, org_term);
}

void	set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ICANON | ECHO);
	new_term->c_cc[VMIN] = 1;
	new_term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void	reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

/* 시그널 처리 */

void	signal_handler_interactive_mode(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal_interactive_mode(void)
{
	signal(SIGINT, signal_handler_interactive_mode);
	signal(SIGQUIT,SIG_IGN);
}

void	set_signal_bash_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc_mode(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}


int main(int argc, char *argv[], char *envp[])
{
	char				*input;
	int					stdio_fd[2];
	int					ch;
	struct termios		org_term;
	struct termios		new_term;
	t_info				info;

	ft_memset(&info, 0, sizeof(info));
	info.envs = save_env(envp);
	info.envp_bash = envp;
	save_input_mode(&org_term);
	set_input_mode(&new_term);
	while (1)
	{
		set_signal_interactive_mode();
		stdio_fd[0] = dup(STDIN_FILENO);
		stdio_fd[1] = dup(STDOUT_FILENO);
		info.pipes = 0;
		info.redirects = 0;
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_putstr_fd("exit\n", 2);
			exit(EXIT_SUCCESS);
		}
		add_history(input);
		if (parse(input, &info) == QUOTE_ERROR)
		{
			ft_putstr_fd("minishell: syntax error quote is not closed\n", 2);
			continue ;
		}
		if (args_check(&info) != ERROR && divide_pipe(&info) != ERROR)
		{
			//print_cmd_deque(&info);
			exec_commands(&info);
		}
		free(input);
		//free structs
		dup2(stdio_fd[0], 0);
		dup2(stdio_fd[1], 1);
		close(stdio_fd[0]);
		close(stdio_fd[1]);
		reset_input_mode(&org_term);
	}
	return (0);
}
