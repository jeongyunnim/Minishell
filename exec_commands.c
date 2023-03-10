/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/10 18:14:04 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_handler(t_info *info)
{
	t_arg	*temp;
	char	*heredoc_input;
	int		temp_fd;
	int		i;

	i = 0;
	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special == HEREDOC)
		{
			temp_fd = open(HEREDOC_TEMP, O_WRONLY|O_CREAT|O_TRUNC, 0600);
			//fds[i] = open(HEREDOC_TEMP, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC);
			while (1)
			{
				heredoc_input = readline("> ");
				if (ft_strncmp(temp->next->arg, heredoc_input, ft_strlen(heredoc_input)) == 0)
					break ;
				write(temp_fd, heredoc_input, ft_strlen(heredoc_input));
				write(temp_fd, "\n", 1);
				printf("%d: %s\n", temp_fd, heredoc_input);
			}
			open(HEREDOC_TEMP, O_RDONLY); // 현재 받아온 델리미터를 현재의 fd 값을 가리키게 할 수 있을까?
			close(temp_fd);
			unlink(HEREDOC_TEMP);
		}
		temp = temp->next;
	}
	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special == REDIRECT_IN)
		{
			open("tempfilename", O_RDONLY);
		}
		else if (temp->special == REDIRECT_OUT)
		{
			open("tempfilename", O_RDONLY);
		}
		else if (temp->special == APPEND)
		{
			open("tempfilename", O_RDONLY);
		}
		temp = temp->next;
	}
	return (0);
}

int	exec_commands(t_info *info)
{
	pid_t	pid;
	int		fd[2];
	int		temp;
	int		i;


	redirection_handler(info);
	return (0);
}
