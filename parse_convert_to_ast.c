
#include "minishell.h"


t_ast_node *parse_command(t_arg_deque *args)
{
	t_arg		*temp;
	t_ast_node	*node;

	temp = args->head;
	node = NULL;
	if (temp == NULL)
	{
		return (NULL);
	}
	while (temp->special == PIPE)
	{
		node = create_ast_node(PIPE, NULL);
		node->left = parse_command(args->head);
		node->right = parse_command(temp);
	}
	if (temp->special != 0)
	{
		//히어독 처리..는 어떻게 하지? 일단 노드에만 담아주도록 하자.
		node = create_ast_node(temp->special, temp->arg);
		//node->left = 
	}
}

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
