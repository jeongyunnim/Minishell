/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:39:29 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/22 19:18:31 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_temp_file(t_arg *red, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input == NULL || \
		ft_strncmp(red->arg, input, ft_strlen(red->arg) + 1) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	if (input != NULL)
		free(input);
}

int	open_and_write_temp_file(t_arg_deque *redirects)
{
	t_arg	*move_red;
	char	*temp_file;
	int		temp_fd;

	move_red = redirects->head;
	while (move_red != NULL)
	{
		if (move_red->special == HEREDOC)
		{
			temp_file = gen_temp_file_name(1);
			temp_fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
			if (temp_fd < 0)
				exit(EXIT_FAILURE);
			write_temp_file(move_red, temp_fd);
			free(move_red->arg);
			move_red->arg = ft_strdup(temp_file);
			close(temp_fd);
		}
		move_red = move_red->next;
	}
	return (0);
}

int	name_temp_file(t_arg_deque *redirects)
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
			temp_file = gen_temp_file_name(1);
			free(move_red->arg);
			move_red->arg = ft_strdup(temp_file);
		}
		move_red = move_red->next;
	}
	return (0);
}

static void	child_run_for_heredoc(t_cmd *temp)
{
	while (temp != NULL)
	{
		if (temp->redirections != NULL)
		{
			set_signal_mode(HEREDOC_M);
			open_and_write_temp_file(temp->redirections);
		}
		temp = temp->next;
	}
	exit(EXIT_SUCCESS);
}

int	heredoc_handler(t_info *info)
{
	t_cmd	*temp;
	pid_t	pid;
	int		flag;
	int		status;

	temp = info->cmds->head;
	pid = fork();
	if (pid == ERROR)
		return (ERROR);
	else if (pid == 0)
		child_run_for_heredoc(temp);
	else
	{
		set_signal_mode(FORK_PARENT_M);
		waitpid(pid, &status, 0);
		if (status == 2)
			return (SIGINT);
		while (temp != NULL)
		{
			if (temp->redirections != NULL)
				name_temp_file(temp->redirections);
			temp = temp->next;
		}
	}
	return (0);
}
