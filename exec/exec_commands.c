/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cat_env_name_value(char *name, char *value)
{
	char	*full_env;
	char	*temp;

	full_env = ft_strdup(name);
	temp = full_env;
	full_env = ft_strjoin(full_env, "=");
	free(temp);
	temp = full_env;
	full_env = ft_strjoin(full_env, value);
	free(temp);
	return (full_env);
}

char	**envlist_to_arry(t_env_deque *envs)
{
	t_env	*env;
	char	**array;
	int		cnt;
	int		i;

	cnt = 0;
	env = envs->head;
	while (env != NULL)
	{
		cnt++;
		env = env->next;
	}
	array = (char **)ft_calloc(sizeof(char *), (cnt + 1));
	i = 0;
	env = envs->head;
	while (env != NULL)
	{
		if (env->value != NULL)
			array[i++] = cat_env_name_value(env->name, env->value);
		env = env->next;
	}
	return (array);
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

int	fork_and_run(t_info *info, t_pipe_index *index, t_cmd **cmd_line)
{
	if (index->pid == -1)
	{
		print_system_error(FORK_ERROR);
		return (ERROR);
	}
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
				return (print_system_error(PIPE_ERROR));
		}
		if (info->pipes == 0 && isbuiltin(cmd_line->cmd_args) == 1)
			return (exec_one_builtin(info, cmd_line));
		index.pid = fork();
		if (fork_and_run(info, &index, &cmd_line) == ERROR)
			return (ERROR);
		index.i += 1;
	}
	free(info->cmds);
	parent_process_wait(index.pid, info->pipes);
	return (0);
}
