/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/13 21:08:03 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

char	*gen_temp_file_name(void)
{
	static char		name[10];
	char			name_len;
	int				i;

	if (name[5] == 0)
	{
		ft_memcpy(name, "temp/0", 6);
		return (name);
	}
	i = 5;
	while (i < 10)
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

int	isbuiltin(char *cmd)
{
	if (ft_strncmp("echo", cmd, 5) == 0)
	{
		write(1, "이 자리에 echo 와야 함\n", 30);
		//echo 실행
	}
	else if (ft_strncmp("cd", cmd, 3) == 0)
	{
		write(1, "이 자리에 ㅊㅇ 와야 함\n", 28);
		//cd 실행
	}
	else if (ft_strncmp("pwd", cmd, 4) == 0)
	{
		write(1, "이 자리에 pwd 와야 함\n", 29);
		//pwd 실행
	}
	else if (ft_strncmp("export", cmd, 7) == 0)
	{
		write(1, "이 자리에 export 와야 함\n", 32);
		//export 실행
	}
	else if (ft_strncmp("unset", cmd, 6) == 0)
	{
		write(1, "이 자리에 unset 와야 함\n", 31);
		//unset 실행
	}
	else if (ft_strncmp("env", cmd, 4) == 0)
	{
		write(1, "이 자리에 env 와야 함\n", 29);
		//env 실행
	}
	else if (ft_strncmp("exit", cmd, 5) == 0)
	{
		write(1, "이 자리에 exit 와야 함\n", 30);
		//exit 실행
	}
	else
	{
		write(1, "빌트인 처리로 감\n", 24);
	}
		return (0);
	return (1);
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
	fd[0] = -1;
	fd[1] = -1;
	printf("i %d, pipes: %d\n", i, info->pipes);
	while (i <= info->pipes)
	{
		if (i < info->pipes)
		{
			if (pipe(fd) != ERROR)
				return (ERROR);
			temp = fd[0];
		}
		if (info->pipes == 0 && isbuiltin(info->cmds->head->commands_args[0]) == 1)
		{
			//포크뜨지 않기.. 그래야 export a=1 같은 것이 저장이 된다..... ㅜㅜ 
			//바로 실행
		}
		pid = fork();
		printf("pid: %d\n", pid);
		if (pid == -1)
			return (ERROR);
		else if (pid == 0) // 자식 프로세스
		{
			child_process_run(info, i, fd, temp);
		}
		i++;
	}
	// 1. pipe 처리
	// 2. redirection 처리
	// 3. 실행
	return (0);
}
