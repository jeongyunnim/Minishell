
#include "minishell.h"

int	prioritize(t_info *info)
{
	t_arg	*temp;

	temp = info->arguments->head;
	while (temp != NULL)
	{
		printf("----------------------\n\n[input]: %s\n[type]: %d\n\n----------------------\n", temp->arg, temp->special);
		temp = temp->next;
	}
	/*
		1. heredoc -> 임시파일 처리
		2. redirection
		3. 1st instruction
		...

		heredoc이 오류 났을 때 어떻게 하는 것이 좋을지?
	*/
	return (0);
}