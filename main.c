/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:09:56 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/22 20:06:06 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 터미널 모드 설정 */

void	save_input_mode(struct termios *org_term)
{
	tcgetattr(STDIN_FILENO, org_term);
}

void	set_input_mode(struct termios *new_term)
{
	tcgetattr(STDIN_FILENO, new_term);
	new_term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}

void	reset_input_mode(struct termios *org_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

/* 시그널 처리 */

void	init_oldpwd(t_env_deque *env)
{
	t_env	*env_temp;
	int		flag;

	env_temp = env->head;
	flag = 0;
	while (env_temp != NULL)
	{
		if (ft_strncmp(env_temp->name, "OLDPWD", 7) == 0)
		{
			flag = 1;
			break ;
		}
		env_temp = env_temp->next;
	}
	if (flag == 1)
	{
		free(env_temp->value);
		env_temp->value = NULL;
		env_temp->value_len = 0;
		return ;
	}
	env_temp = lstnew_env();
	env_temp->name = ft_strdup("OLDPWD");
	env_temp->name_len = 6;
	append_tail_env(&env->head, &env->tail, env_temp);
}

void	init_info(t_info *info, char *envp[])
{
	ft_memset(info, 0, sizeof(info));
	info->envs = save_env(envp);
	info->home_dir = getenv("HOME");
	init_oldpwd(info->envs);
}

int main(int argc, char *argv[], char *envp[])
{
	char				*input;
	int					stdio_fd[2];
	struct termios		org_term;
	struct termios		new_term;
	t_info				info;

	init_info(&info, envp);
	save_input_mode(&org_term);
	set_input_mode(&new_term);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
		set_signal_mode(INTERACTIVE_M);
		stdio_fd[0] = dup(STDIN_FILENO);
		stdio_fd[1] = dup(STDOUT_FILENO);
		info.pipes = 0;
		info.redirects = 0;
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_putstr_fd("\033[1A", 1);
			ft_putstr_fd("\033[11C", 1);
			ft_putstr_fd("exit\n", 1);
			exit(EXIT_SUCCESS);
		}
		add_history(input);
		if (parse(input, &info) == QUOTE_ERROR)
		{
			ft_putstr_fd("minishell: syntax error quote is not closed\n", 2);
			continue ;
		}
		if (args_check(&info) != ERROR)
		{
			divide_pipe(&info);
			exec_commands(&info);
		}
		else
		{
			free_arg_deque(&info.arguments);
		}
		free(input);
		dup2(stdio_fd[0], 0);
		dup2(stdio_fd[1], 1);
		close(stdio_fd[0]);
		close(stdio_fd[1]);
		reset_input_mode(&org_term);
	}
	return (0);
}
