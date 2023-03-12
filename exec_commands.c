/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 21:23:25 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_temp_file_name(void)
{
	static char		name[255];
	char			name_len;
	int				i;

	if (name[5] == 0)
	{
		ft_memcpy(name, "temp/0", 6);
		return (name);
	}
	i = 5;
	while (i < 255)
	{
		if (name[i] == 0)
			name[i] = '0';
		else if (name[i] == '9')
		{
			name[i] = '0';
			i++;
		}
		else
		{
			name[i]++;
			break ;
		}
	}
	return (name);
}

int	heredoc_handler(t_info *info)
{
	t_cmd	*temp;
	t_arg	*temp_redirect;
	char	*heredoc_input;
	char	*temp_file;
	int		temp_fd;

	temp = info->cmds->head;
	while (temp != NULL)
	{
		if (temp->redirections == NULL)
		{
			temp = temp->next;
			continue ;
		}
		temp_redirect = temp->redirections->head;
		while (temp_redirect != NULL)
		{
			if (temp_redirect->special == HEREDOC)
			{
				temp_file = gen_temp_file_name();
				temp_fd = open(temp_file, O_WRONLY|O_CREAT|O_TRUNC, 0600);
				while (1)
				{
					heredoc_input = readline("> ");
					if (ft_strncmp(temp_redirect->arg, heredoc_input, ft_strlen(heredoc_input)) == 0)
						break ;
					write(temp_fd, heredoc_input, ft_strlen(heredoc_input));
					write(temp_fd, "\n", 1);
				}
				temp_redirect->arg = ft_strdup(temp_file);
				close(temp_fd);
			}
			temp_redirect = temp_redirect->next;
		}
		temp = temp->next;
	}
	return (0);
}

int	exec_commands(t_info *info)
{
	pid_t	pid;
	int		fd[2];
	int		temp;
	int		i;

	if (heredoc_handler(info))
		return (ERROR);
	i = 0;
	ft_memset(fd, 0 , sizeof(fd));
	while (i <= info->pipes)
	{
		if (i < info->pipes)
		{
			if (pipe(fd) != ERROR)
				return (ERROR);
			temp = fd[0];
		}
		pid = fork();
		if (pid == -1)
			return (ERROR); // 이미 생성된 자식 프로세스는 어찌할까?
		else if (pid == 0) // 자식 프로세스 할 거 해
		{
			if (info->pipes == 0)
			{
				//아무것도 하지 않음
			}
			if (i == 0)
			{
				close(fd[0]);
			}
			else if (i == info->pipes)
			{
				// 마지막 파이프는 연결하지 않고 종료.
			}
			//리다이렉션 처리
			//command 찾기.
			//execve(info->cmds->head->commands_args[0], &info->cmds->head->commands_args[0], info->envp_bash);
			write(2, "exec 실행 오류.. 어떻게 해야하는데..\n", 49);
			//exit(어쩌구);
			//전역변수 에러 코드 변환해주기.
		}
		i++;
	}
	// 1. pipe 처리
	// 2. redirection 처리
	// 3. 실행
	return (0);
}
