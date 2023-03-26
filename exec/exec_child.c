/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:40:48 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 16:00:46 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	stdio_to_pipe(t_pipe_index index, int pipes)
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
	if (temp_env == NULL || **cmd == '\0')
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

void	access_check(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		print_error(OPEN_ERROR, cmd);
		exit(127);
	}
	else if (access(cmd, X_OK) == -1)
	{
		print_error(PERMISSION_ERROR, cmd);
		exit(126);
	}
	if (opendir(cmd) != NULL)
	{
		print_error(DIRECTORY_ERROR, cmd);
		exit(126);
	}
}

void	child_process_run(t_cmd *cmd_node, t_pipe_index index, t_info *info)
{
	set_signal_mode(FORK_CHILD_M);
	stdio_to_pipe(index, info->pipes);
	if (handle_redirection(cmd_node->redirections) == ERROR)
		exit(EXIT_FAILURE);
	if (isbuiltin(cmd_node->cmd_args) == 1)
		exit(exec_builtin(cmd_node->cmd_args, info->envs));
	else if (ft_strchr(cmd_node->cmd_args[0], '/') == 0 && \
		check_cmd_in_path(&(cmd_node->cmd_args[0]), info->envs->head) == 0)
	{
		print_error(COMMAND_ERROR, cmd_node->cmd_args[0]);
		exit(127);
	}
	access_check(cmd_node->cmd_args[0]);
	execve(cmd_node->cmd_args[0], cmd_node->cmd_args, \
		envlist_to_arry(info->envs));
}
