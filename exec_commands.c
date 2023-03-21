/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/21 16:22:08 by jeseo            ###   ########.fr       */
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
	static char		name[8];
	char			name_len;
	int				i;

	if (name[5] == 0)
		ft_memcpy(name, "temp/", 5);
	i = 0;
	while (i < 16)
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

int	write_temp_file(t_arg_deque *redirects)
{
	t_arg	*move_red;
	char	*temp_file;
	char	*input;
	int		temp_fd;

	move_red = redirects->head;
	while (move_red != NULL)
	{
		if (move_red->special == HEREDOC)
		{
			temp_file = gen_temp_file_name();
			temp_fd = open(temp_file, O_WRONLY|O_CREAT|O_TRUNC, 0600);
			if (temp_fd < 0)
				return (ERROR); // temp file open 에러.. 처리는 어떻게 해야할까나?
			while (1)
			{
				input = readline("> ");
				if (input == NULL || ft_strncmp(move_red->arg, input, ft_strlen(move_red->arg) + 1) == 0)
					break ;
				if (write(temp_fd, input, ft_strlen(input)) == ERROR)
				{
					free(input);
					return (HEREDOC);
				}
				write(temp_fd, "\n", 1);
				free(input);
			}
			if (input != NULL)
				free(input);
			free(move_red->arg);
			move_red->arg = ft_strdup(temp_file);
			close(temp_fd);
		}
		move_red = move_red->next;
	}
	return (0);
}

int	heredoc_handler(t_info *info)
{
	t_cmd	*temp;
	pid_t	pid;

	temp = info->cmds->head;
	while (temp != NULL)
	{
		if (temp->redirections != NULL)
		{
			set_signal_mode(HEREDOC_M);
			if (write_temp_file(temp->redirections) == ERROR)
				return (ERROR);
			set_signal_mode(INTERACTIVE_M);
		}
		temp = temp->next;
	}
	return (0);
}

int	isbuiltin(char **cmd_args)
{
	char	*cmd;

	if (cmd_args == NULL || *cmd_args == NULL)
		return (1);
	cmd = cmd_args[0];
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (1);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (1);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (1);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (1);
	else
		return (0);
}

void	parent_process_wait(pid_t pid, int pipes)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i <= pipes)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	printf("status %d\n", status); // status 잘 처리하기..
}

int	exec_builtin(char **cmd_line, t_env_deque *envs)
{
	if (cmd_line[0] == NULL || cmd_line[0][0] == '\0')
		return (0);
	if (ft_strncmp("echo", cmd_line[0], 5) == 0)
	{
		ft_putstr_fd("이 자리에 echo 와야 함\n", 2);
		return (0);
	}
	else if (ft_strncmp("cd", cmd_line[0], 3) == 0)
	{
		write(1, "이 자리에 cd 와야 함\n", 28);
		return (0);
		//cd 실행
	}
	else if (ft_strncmp("pwd", cmd_line[0], 4) == 0)
	{
		write(1, "이 자리에 pwd 와야 함\n", 29);
		return (0);
		//pwd 실행
	}
	else if (ft_strncmp("export", cmd_line[0], 7) == 0)
	{
		write(1, "이 자리에 export 와야 함\n", 32);
		return (0);
		//export 실행
	}
	else if (ft_strncmp("unset", cmd_line[0], 6) == 0)
	{
		write(1, "이 자리에 unset 와야 함\n", 31);
		return (0);
		//unset 실행
	}
	else if (ft_strncmp("env", cmd_line[0], 4) == 0)
	{
		write(1, "이 자리에 env 와야 함\n", 29);
		return (0);
		//env 실행
	}
	else if (ft_strncmp("exit", cmd_line[0], 5) == 0)
	{
		write(1, "이 자리에 exit 와야 함\n", 30);
		return (0);
		//exit 실행
	}
	return (1);
}

int	exec_commands(t_info *info)
{
	pid_t			pid;
	t_cmd			*cmd_line;
	t_pipe_index	index;

	if (heredoc_handler(info))
		return (ERROR);
	index.fd[0] = -1;
	index.fd[1] = -1;
	index.prev_pipe_read = -1;
	index.i = 0;
	cmd_line = pop_head_cmd(&info->cmds->head);
	while (cmd_line != NULL)
	{
		if (index.i < info->pipes)
		{
			if (pipe(index.fd) == ERROR)
				return (ERROR);
		}
		if (info->pipes == 0 && isbuiltin(cmd_line->commands_args) == 1)
		{
			if (handle_redirection(cmd_line->redirections) != ERROR)
			{
				exec_builtin(cmd_line->commands_args, info->envs);
			}
			free_cmd_node(&cmd_line);
			free(info->cmds);
			return (0);
		}
		pid = fork();
		if (pid == -1)
			return (ERROR);
		else if (pid == 0)
		{
			set_signal_mode(FORK_CHILD_M);
			child_process_run(cmd_line, index, info);
			exit(EXIT_SUCCESS);
		}
		else
		{
			set_signal_mode(FORK_PARENT_M);
			free_cmd_node(&cmd_line);
			cmd_line = pop_head_cmd(&(info->cmds->head));
			if (index.prev_pipe_read != -1)
				close(index.prev_pipe_read);
			if (index.fd[1] != -1)
				close(index.fd[1]);
			index.prev_pipe_read = index.fd[0];
		}
		index.i += 1;
	}
	free(info->cmds);
	parent_process_wait(pid, info->pipes); // 여기까지 오기 전에 자식 프로세스가 끝이 나버리면...??
	return (0);
}
