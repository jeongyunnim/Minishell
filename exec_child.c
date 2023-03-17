/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:40:48 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/16 15:23:35 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdio_to_pipe(t_cmd *cmd_line, t_pipe_index index, int pipes)
{
	/* 파일에 fd값 저장하는 부분 */
	FILE *out;
	char *temp;
	static int i;
	i++;
	temp = ft_itoa(i);
	out = fopen(temp, "w");
	fprintf(out, "fd[0]: %d fd[1]: %d prev: %d\n", index.fd[0], index.fd[1], index.prev_pipe_read);
	fclose(out);
	free(temp);

	if (pipes == 0)
		return (0);
	if (index.i == 0)
	{
		//첫 번째 커맨드는 입력은 STDIN(0)으로 내버려 둔다.
		close(index.fd[0]);
		dup2(index.fd[1], STDOUT_FILENO);
		close(index.fd[1]);
	}
	else if (index.i == pipes) // 마지막 거..
	{
		//STDIN(0)을 temp(이전 fd[0])으로
		//마지막 커맨드는 STDOUT(1)을 연결하지 않고 종료

		// 안 쓰는 파이프 닫아줘야 함..

		dup2(index.prev_pipe_read, STDIN_FILENO);
		close(index.prev_pipe_read);
	}
	else
	{
		//0을 temp(이전 fd[0])으로
		//1을 pipe의 fd[1]로
		
		// 안 쓰는 파이프 닫아줘야 함..
		close(index.fd[0]);
		dup2(index.prev_pipe_read, STDIN_FILENO);
		close(index.prev_pipe_read);
		dup2(index.fd[1], STDOUT_FILENO);
		close(index.fd[1]);
	}
	return (0);
}

int	check_access_read(char *file_name, t_special type)
{
	int		fd;

	if (access(file_name, F_OK) == -1)
		return (OPEN_ERROR);
	else if (access(file_name, R_OK) == -1)
	{
		return (PERMISSION_ERROR);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (OPEN_ERROR);
	if (type == HEREDOC)
		unlink(file_name);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	check_access_write(char *file_name, t_special type)
{
	int fd;

	if (access(file_name, F_OK) == -1)
	{
		fd = open(file_name, O_WRONLY|O_CREAT, 0644);
		if (fd < 0)
			return (OPEN_ERROR);
	}
	else if (opendir(file_name) != NULL)
		return (DIRECTORY_ERROR);
	else if (access(file_name, W_OK) == -1)
		return (PERMISSION_ERROR);
	else
	{
		if (type == REDIRECT_OUT)
			fd = open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		else
			fd = open(file_name, O_WRONLY|O_CREAT|O_APPEND, 0644);
		if (fd < 0)
			return (OPEN_ERROR);		
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	handle_redirection(t_arg_deque *redirections)
{
	t_arg	*red;
	int		fd;

	if (redirections == NULL)
		return (0);
	red = redirections->head;
	while (red != NULL)
	{
		fd = -1;
		if (red->special == HEREDOC || red->special == REDIRECT_IN)
			fd = check_access_read(red->arg, red->special);
		else
			fd = check_access_write(red->arg, red->special);
		if (fd < 0)
		{
			if (fd == PERMISSION_ERROR)
				write(2, "minishell: Permission denied\n", 29);
			else if (fd == OPEN_ERROR)
				write(2, "minishell: No such file or directory\n", 37);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(red->arg, 2);
				ft_putstr_fd(": Is a directory\n", 2);
			}
			return (ERROR);
		}
		red = red->next;
	}
	return (0);
}

int	check_cmd_in_path(char **cmd, t_env_deque *envs)
{
	t_env	*temp_env;
	char	**paths;
	char	*temp_char;
	int 	i;

	temp_env = envs->head;
	if (ft_strchr((*cmd), '/') != 0)
		return (1);
	while (temp_env != NULL)
	{
		if (ft_strncmp(temp_env->name, "PATH", 5) == 0)
			break;
		temp_env = temp_env->next;
	}
	paths = ft_split(temp_env->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		temp_char = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp_char);
		temp_char = paths[i];
		paths[i] = ft_strjoin(paths[i], *cmd);
		free(temp_char);
		if (access(paths[i], F_OK) == 0)
		{
			*cmd = paths[i];
			i++;
			while (paths[i] != NULL)
			{
				free(paths[i]);
				i++;
			}
			free(paths);
			return (1);
		}
		free(paths[i]);
		i++;
	}
	free(paths);
	return (0);
}

int	child_process_run(t_cmd *cmd_node, t_pipe_index index, t_info *info)
{
	char	*cmd;

	stdio_to_pipe(cmd_node, index, info->pipes);
	if (handle_redirection(cmd_node->redirections) == ERROR)
	{
		exit(EXIT_FAILURE);
	}
	if (exec_builtin(cmd_node->commands_args, info->envs) == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (check_cmd_in_path(&(cmd_node->commands_args[0]), info->envs) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_node->commands_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	printf("exec: %s\n", cmd_node->commands_args[0]);
	execve(cmd_node->commands_args[0], cmd_node->commands_args, info->envp_bash);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_node->commands_args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(EXIT_FAILURE);
	//전역변수 에러 코드 변환해주기.
	return (0);
}
