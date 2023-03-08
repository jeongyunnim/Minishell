
#include "minishell.h"

/* 우선순위를 정해서 실행하고, 명령 실행 단위(파이프 단위)로 명령 노드를 따로 만들 예정.*/
int	convert_to_ast(t_info *info)
{
	t_arg	*temp;

	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special != 0 && (temp->next == NULL || temp->next->special != 0))
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, temp->arg, strlen(temp->arg));
			write(2, "\'\n", 2);
			return (ERROR);
		}
		if (temp->special == PIPE)
			info->pipes++;
		else if (temp->special != NONE)
			info->redirects++;
		printf("----------------------\n\n[input]: %s\n[type]: %d\n\n----------------------\n", temp->arg, temp->special);
		temp = temp->next;
	}
	/*
		//이 전에 pipe를 먼저 연결을 해놓는 것이 좋겠다는 거지?
		1. heredoc -> 임시파일 처리
		2. redirection + 리다이렉션은 뒤에 항상 파일이 와야 한다. <(redirection) >(redirection) >>(append)  || << 는 heredoc이므로 나중에 처리.

		cat < a > b > c << d | wc -l | grep 0

		<<a | cat 은 어쩌지?

		3. 1st instruction
		...

		heredoc이 오류 났을 때 어떻게 하는 것이 좋을지?
	*/
	return (0);
}