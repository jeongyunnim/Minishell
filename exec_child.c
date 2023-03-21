/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:40:48 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/21 19:22:29 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdio_to_pipe(t_cmd *cmd_line, t_pipe_index index, int pipes)
{
	if (pipes == 0)
		return (0);
	if (index.i == 0)
	{
		close(index.fd[0]);
		dup2(index.fd[1], STDOUT_FILENO);
		close(index.fd[1]);
	}
	else if (index.i == pipes)
	{
		dup2(index.prev_pipe_read, STDIN_FILENO);
		close(index.prev_pipe_read);
	}
	else
	{
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
		return (PERMISSION_ERROR);
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
	int	fd;

	if (access(file_name, F_OK) == -1)
	{
		fd = open(file_name, O_WRONLY | O_CREAT, 0644);
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
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	gen_temp_file_name(0);
	while (red != NULL)
	{
		fd = -1;
		if (red->special == HEREDOC || red->special == REDIRECT_IN)
		{
			if (red->special == HEREDOC)
			{
				free(red->arg);
				red->arg = ft_strdup(gen_temp_file_name(1));
			}
			fd = check_access_read(red->arg, red->special);
		}
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

void	cat_path_cmd(char **paths, char *cmd)
{
	char	*temp_char;

	temp_char = *paths;
	*paths = ft_strjoin(*paths, "/");
	free(temp_char);
	temp_char = *paths;
	*paths = ft_strjoin(*paths, cmd);
	free(temp_char);
}

int	check_cmd_in_path(char **cmd, t_env *temp_env)
{
	char	**dirs;
	int		i;
	int		command_flag;

	while (temp_env != NULL && ft_strncmp("PATH", temp_env->name, 5) != 0)
		temp_env = temp_env->next;
	if (temp_env == NULL)
		return (0);
	dirs = ft_split(temp_env->value, ':');
	command_flag = 0;
	i = 0;
	while (dirs[i] != NULL)
	{
		cat_path_cmd(&dirs[i], *cmd);
		if (command_flag == 0 && access(dirs[i], F_OK) == 0)
		{
			free(*cmd);
			*cmd = dirs[i++];
			command_flag = 1;
		}
		free(dirs[i++]);
	}
	free(dirs);
	return (command_flag);
}

int	child_process_run(t_cmd *cmd_node, t_pipe_index index, t_info *info)
{
	stdio_to_pipe(cmd_node, index, info->pipes);
	if (handle_redirection(cmd_node->redirections) == ERROR)
		exit(EXIT_FAILURE);
	if (exec_builtin(cmd_node->commands_args, info->envs) == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strchr(cmd_node->commands_args[0], '/') == 0 && \
		check_cmd_in_path(&(cmd_node->commands_args[0]), info->envs->head) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_node->commands_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	dprintf(2, "exec: %s\n", cmd_node->commands_args[0]);
	execve(cmd_node->commands_args[0], cmd_node->commands_args, NULL);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_node->commands_args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(EXIT_FAILURE);
	//전역변수 에러 코드 변환해주기.
	return (0);
}
