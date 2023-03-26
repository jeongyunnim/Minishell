/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:31:01 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parent_process_wait(pid_t pid, int pipes)
{
	int	status;
	int	last_pid_status;
	int	i;

	i = 0;
	status = 0;
	last_pid_status = 0;
	while (i <= pipes)
	{
		if (waitpid(-1, &status, 0) == pid)
			last_pid_status = status;
		i++;
	}
	if (WIFEXITED(last_pid_status) == 1)
		g_exit_code = WEXITSTATUS(last_pid_status);
	else if (WIFSIGNALED(last_pid_status) == 1)
		exited_by_signal(last_pid_status);
}

int	name_temp_file(t_arg_deque *redirects)
{
	t_arg	*move_red;
	char	*temp_file;

	move_red = redirects->head;
	while (move_red != NULL)
	{
		if (move_red->special == HEREDOC)
		{
			temp_file = gen_temp_file_name(1);
			free(move_red->arg);
			move_red->arg = ft_strdup(temp_file);
		}
		move_red = move_red->next;
	}
	return (0);
}

void	parent_process_run(t_cmd **cmd_line, t_pipe_index *index, t_info *info)
{
	reset_input_mode(&info->org_term);
	set_signal_mode(FORK_PARENT_M);
	free_cmd_node(cmd_line);
	*cmd_line = pop_head_cmd(&(info->cmds->head));
	init_pipe_index(index, 1);
}

int	parent_run_for_heredoc(t_cmd *temp, pid_t pid)
{
	int		status;

	set_signal_mode(FORK_PARENT_M);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) == 1)
	{
		g_exit_code = 1;
		return (ERROR);
	}
	while (temp != NULL)
	{
		if (temp->redirections != NULL)
			name_temp_file(temp->redirections);
		temp = temp->next;
	}
	return (0);
}
