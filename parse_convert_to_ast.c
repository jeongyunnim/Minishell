/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_convert_to_ast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:28 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/11 20:48:59 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_ast_node *parse_command(t_arg_deque *args)
{
	t_arg		*temp;
	t_ast_node	*node;

	temp = pop_head_arg(args->head);
	if (temp == NULL)
		return (NULL);
	node = create_ast_node(temp->special, temp->arg);
	free(temp->arg);
	free(temp);
	if (temp->special == PIPE)
	{
		node->left = parse_command(args);
		node->left = parse_command(args);
	}
	else
	{
		node->right = parse_command(args);
	}
	return (node);
}

int	convert_to_ast(t_info *info)
{
	t_arg		*temp;
	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special != 0 && (temp->next == NULL || temp->next->special != 0))
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, temp->arg, ft_strlen(temp->arg));
			write(2, "\'\n", 2);
			return (ERROR);
		}
		if (temp->special == PIPE)
			info->pipes++;
		else if (temp->special != NONE)
			info->redirects++;
		printf("----------------------\n\n[input]: %s\n[type]: %d\n\n----------------------\n", temp->arg, temp->special);
		temp = temp->next;
		info->root = parse_command(info->arguments);
		return (0);
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
