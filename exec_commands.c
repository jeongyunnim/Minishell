/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/10 14:51:48 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_handler(t_info *info)
{
	t_arg	*temp;
	char	*heredoc_input;
	int		*fds;
	int		temp_fd;
	int		i;

	fds = ft_calloc(info->redirects, sizeof(int));
	i = 0;
	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special == HEREDOC)
		{
			fds[i] = open("./temp/temp", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC);
			temp_fd = dup(fds[i]);
			while (1)
			{
				heredoc_input = readline("> ");
				if (ft_strncmp(temp->next->arg, heredoc_input, ft_strlen(heredoc_input)) == 0)
					break ;
				write(temp_fd, heredoc_input, ft_strlen(heredoc_input));
				write(temp_fd, "\n", 1);
				printf("%d: %s\n", fds[i], heredoc_input);
			}
			close(temp_fd);
			i++;
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
