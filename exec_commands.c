/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 16:39:33 by jeseo            ###   ########.fr       */
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

char	*gen_temp_file_name(int flag)
{
	static char		name[8];
	static int		i;

	if (flag == 0)
	{
		i = 0;
		return (NULL);
	}
	if (i == 0 || i == 16)
	{
		ft_memcpy(name, "temp/", 5);
		i = 0;
	}
	if (i > 9)
	{
		name[5] = '1';
		name[6] = i - 10 + '0';
	}
	else
	{
		name[5] = i + '0';
		name[6] = '\0';
	}
	i++;
	return (name);
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

void	parent_process_wait(t_info *info, pid_t pid, int pipes)
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
	if (WIFEXITED(status) == 1)
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 1)
		exited_by_signal(info, status);
}

int	exec_builtin(char **cmd_line, t_env_deque *envs)
{
	if (cmd_line[0] == NULL || cmd_line[0][0] == '\0')
		return (0);
	if (ft_strncmp("echo", cmd_line[0], 5) == 0)
		ft_echo(cmd_line);
	else if (ft_strncmp("cd", cmd_line[0], 3) == 0)
		ft_cd(cmd_line, envs);
	else if (ft_strncmp("pwd", cmd_line[0], 4) == 0)
		ft_pwd(envs);
	else if (ft_strncmp("export", cmd_line[0], 7) == 0)
		ft_export(cmd_line, envs);
	else if (ft_strncmp("unset", cmd_line[0], 6) == 0)
		ft_unset(cmd_line, envs);
	else if (ft_strncmp("env", cmd_line[0], 4) == 0)
		ft_env(cmd_line, envs);
	else if (ft_strncmp("exit", cmd_line[0], 5) == 0)
		ft_exit(cmd_line);
	else
		return (1);
	return (0);
}

char	**envlist_to_arry(t_env_deque *envs)
{
	t_env	*env;
	char	**array;
	char	*temp;
	int		cnt;
	int		i;

	i = 0;
	env = envs->head;
	while (env != NULL)
	{
		cnt++;
		env = env->next;
	}
	array = (char **)ft_calloc(sizeof(char *), (cnt + 1));
	env = envs->head;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			temp = array[i];
			array[i] = ft_strjoin(env->name, "=");
			free(temp);
			temp = array[i];
			array[i] = ft_strjoin(array[i], env->value);
			free(temp);
		}
		env = env->next;
		i++;
	}
	return (array);
}

int	exec_one_builtin(t_info *info, t_cmd *cmd_line)
{
	if (handle_redirection(cmd_line->redirections) != ERROR)
		exec_builtin(cmd_line->cmd_args, info->envs);
	free_cmd_node(&cmd_line);
	free(info->cmds);
	return (0);
}

void	init_pipe_index(t_pipe_index *index, int flag)
{
	if (flag == 0)
	{
		index->fd[0] = -1;
		index->fd[1] = -1;
		index->prev_pipe_read = -1;
		index->i = 0;
		index->pid = 0;
	}
	else
	{
		if (index->prev_pipe_read != -1)
			close(index->prev_pipe_read);
		if (index->fd[1] != -1)
			close(index->fd[1]);
		index->prev_pipe_read = index->fd[0];
	}
}

void	parent_process_run(t_cmd **cmd_line, t_pipe_index *index, t_info *info)
{
	set_signal_mode(FORK_PARENT_M);
	free_cmd_node(cmd_line);
	*cmd_line = pop_head_cmd(&(info->cmds->head));
	init_pipe_index(index, 1);
}

int	fork_and_run(t_info *info, t_pipe_index *index, t_cmd **cmd_line)
{
	if (index->pid == -1)
		return (ERROR);
	else if (index->pid == 0)
		child_process_run(*cmd_line, *index, info);
	else
		parent_process_run(cmd_line, index, info);
	return (0);
}

int	exec_commands(t_info *info)
{
	t_cmd			*cmd_line;
	t_pipe_index	index;

	init_pipe_index(&index, 0);
	gen_temp_file_name(0);
	if (heredoc_handler(info) != 0)
		return (ERROR);
	cmd_line = pop_head_cmd(&info->cmds->head);
	while (cmd_line != NULL)
	{
		if (index.i < info->pipes)
		{
			if (pipe(index.fd) == ERROR)
				return (ERROR);
		}
		if (info->pipes == 0 && isbuiltin(cmd_line->cmd_args) == 1)
			return (exec_one_builtin(info, cmd_line));
		index.pid = fork();
		if (fork_and_run(info, &index, &cmd_line) == ERROR)
			return (ERROR);
		index.i += 1;
	}
	free(info->cmds);
	parent_process_wait(info, index.pid, info->pipes);
	return (0);
}

//exec_commands()에 부모가 기다리기 전에 자식이 끝나버리면 어쩌지?