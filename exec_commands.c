/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 15:02:03 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gen_temp_file_name(void)
{
	static char		name[255];
	char			name_len;
	int				i;

	if (name[5] == 0)
	{
		ft_memcpy(name, "temp/0", 6);
		return (name);
	}
	i = 5;
	while (i < 255)
	{
		if (name[i] == 0)
			name[i] = '0';
		else if (name[i] == '9')
		{
			name[i] = '0';
			i++;
		}
		else
		{
			name[i]++;
			break ;
		}
	}
	return (name);
}

int	heredoc_handler(t_info *info)
{
	t_arg	*temp;
	char	*heredoc_input;
	char	*temp_file;
	int		temp_fd;

	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special == HEREDOC)
		{
			temp_file = gen_temp_file_name();
			temp_fd = open(temp_file, O_WRONLY|O_CREAT|O_TRUNC, 0600);
			while (1)
			{
				heredoc_input = readline("> ");
				if (ft_strncmp(temp->next->arg, heredoc_input, ft_strlen(heredoc_input)) == 0)
					break ;
				write(temp_fd, heredoc_input, ft_strlen(heredoc_input));
				write(temp_fd, "\n", 1);
				printf("%d: %s\n", temp_fd, heredoc_input);
			}
			free(temp->next->arg);
			temp->next->arg = ft_strdup(temp_file);
			if (temp->next->arg == NULL)
			{
				write(2, "파일명 문자열 멀록 실패\n", 34);
				return (ERROR);
			}
			close(temp_fd);
		}
		temp = temp->next;
	}
	// temp = info->arguments->head; // 미리 열어버릴 수 없음.
	// while (temp != NULL)
	// {
	// 	if (temp->special == REDIRECT_IN)
	// 	{
	// 		open(temp->next->arg, O_RDONLY);
	// 	}
	// 	else if (temp->special == REDIRECT_OUT)
	// 	{
	// 		open(temp->next->arg, O_WRONLY|O_CREAT|O_TRUNC);
	// 	}
	// 	else if (temp->special == APPEND)
	// 	{
	// 		open(temp->next->arg, O_WRONLY|O_CREAT);
	// 	}
	// 	temp = temp->next;
	// }
	return (0);
}

int	exec_commands(t_info *info)
{
	pid_t	pid;
	int		fd[2];
	int		temp;
	int		i;

	if (heredoc_handler(info))
		return (ERROR);
	return (0);
}
