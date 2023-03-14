/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:40:48 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/14 18:24:48 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stdio_to_pipe(t_cmd *cmd_line, t_pipe_index index, int pipes)
{
	FILE *out;
	char *temp;
	static int i;

	i++;
	temp = ft_itoa(i);
	out = fopen(temp, "w");
	fprintf(out, "fd[0]: %d fd[1]: %d\n", index.fd[0], index.fd[1]);
	fclose(out);
	free(temp);
	if (pipes == 0)
	{
		return (0);
	}
	if (index.i == 0)
	{
		//첫 번째 커맨드는 입력은 STDIN(0)으로 내버려 둔다.
		close(index.fd[0]);
		dup2(index.fd[1], STDOUT_FILENO);
		close(index.fd[1]);
	}
	else if (index.i == pipes)
	{
		//STDIN(0)을 temp(이전 fd[0])으로
		//마지막 커맨드는 STDOUT(1)을 연결하지 않고 종료.
		dup2(index.prev_pipe_read, STDIN_FILENO);
		close(index.prev_pipe_read);
	}
	else
	{
		//0을 temp(이전 fd[0])으로
		//1을 pipe의 fd[1]로
		dup2(index.prev_pipe_read, STDIN_FILENO);
		dup2(index.fd[1], STDOUT_FILENO);
		close(index.prev_pipe_read);
		close(index.fd[1]);
	}
	return (0);
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
		{
			fd = open(red->arg, O_RDONLY); // 어차피 acess 함수에서 리드 권한으로 열 건지 쓰기 권한으로 열 건지 체크를 해야할 것이다.
			if (fd < 0)
				break ;
			if (red->special == HEREDOC)
				unlink(red->arg);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (red->special == REDIRECT_OUT)
		{
			fd = open(red->arg, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if (fd < 0)
				break ;
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (red->special == APPEND)
		{
			fd = open(red->arg, O_WRONLY|O_CREAT|O_APPEND, 0644);
			if (fd < 0)
				break ;
		}
		if (fd < 0)
		{
			//open 에러 마다 exit code 변경시켜주기.
			write(2, "minishell: Permission denied\n", 29);
			write(2, "minishell: No such file or directory\n", 37);
		}
		red = red->next;
	}
	return (0);
}


int	child_process_run(t_cmd *cmd_node, t_pipe_index index, t_info *info)
{
	stdio_to_pipe(cmd_node, index, info->pipes);
	handle_redirection(cmd_node->redirections); // command 노드가 NULL이면 어디서 처리가 되는가?
	printf("exec: %s\n", cmd_node->commands_args[0]);
	if (exec_builtin(cmd_node->commands_args) == 0)
	{
		exit(EXIT_SUCCESS);
	}
	printf("no빌트\n");
	//command 찾기.
	execve(cmd_node->commands_args[0], cmd_node->commands_args, info->envp_bash);
	write(2, "exec 실행 오류.. 어떻게 해야하는데..\n", 49);
	//전역변수 에러 코드 변환해주기.
	return (0);
}
