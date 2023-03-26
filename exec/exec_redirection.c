/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:32:09 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			return (redirection_error(fd, red->arg));
		red = red->next;
	}
	return (0);
}
