/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/05 20:52:52 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_to_execute_command(t_info *info)
{
	pid_t	pid;
	int		fd[2];
	int		temp;
	int		i;

/* 명령어 파스트리로 만들어 봅시다. */
	//i = 0;
	//while (i <= info->pipes)
	//{
	//	if (i < info->pipes)
	//	{
	//		pipe(fd);
	//		temp = fd[0];
	//	}
	//	pid = fork();
	//	if (pid == ERROR)
	//	{
	//		write(2, "자식 프로세스 생성 오류\n", 34);
	//		return (ERROR);
	//	}
	//	else if (pid == 0)
	//	{
	//		if (i == 0)
	//		{
	//			close(fd[0]);
	//		}
	//		dup2(1, fd[1]);
	//		close(fd[1]);
	//		//리다이렉션 처리
	//		execl("/bin/echo", "아들입니다. 에코로 출력했어요");
	//		write(2, "명령어 실행 오류\n", 34);
	//	}
	//	i++;
	//}
	return (0);
}
