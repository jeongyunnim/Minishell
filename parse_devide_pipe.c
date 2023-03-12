/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_devide_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:28 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 17:10:01 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_node_init(t_cmd	**node, t_arg_deque *args)
{
	t_arg	*temp;
	int		cmd_arg_count;
	int		redirect_flag;

	redirect_flag = 0;
	if (*node == NULL)
		return (ERROR);
	temp = args->head;
	while (temp == NULL)
	{
		if (temp->special == PIPE)
			return (0);
		else if (temp->special == NONE)
			cmd_arg_count++;
		else
			redirect_flag++;
		temp = temp->next;
	}
	(*node)->commands_args = (char **)ft_calloc(sizeof(char *), cmd_arg_count);
	if ((*node)->commands_args == NULL)
		return (ERROR);
	if (redirect_flag > 0)
	{
		(*node)->redirections = (t_arg_deque *)ft_calloc(sizeof(t_arg_deque), 1);
		if ((*node)->redirections == NULL)
			return (ERROR);
	}
	return (0);
}

int devide_pipe(t_info	*info)
{
	t_arg	*temp;
	t_arg	*arg_node;
	t_cmd	*new;
	int		i;

	info->cmds = ft_calloc(sizeof(t_cmd_deque), 1);
	if (info->cmds == NULL)
	{
		return (ERROR);
	}
	temp = info->arguments->head;
	while (temp != NULL)
	{
		new = lstnew_cmd();
		if (cmd_node_init(&new, info->arguments) == ERROR)
		{
			//지금까지 할당된 다른 노드들 프리.
			return (ERROR);
		}
		i = 0;
		while (arg_node != NULL)
		{
			arg_node = pop_head_arg(&(info->arguments->head));
			if (arg_node->special == PIPE)
			{
				free(arg_node->arg);
				free(arg_node);
				break ;
			}
			else if (temp->special == NONE)
			{
				new->commands_args[i] = arg_node->arg;
				free(arg_node);
				i++;
			}
			else
			{
				free(arg_node->arg);
				arg_node->arg = info->arguments->head->arg;
				append_head_arg(&new->redirections, arg_node);
				arg_node = pop_head_arg(&(info->arguments->head));
				free(arg_node);
			}
		}
		append_head_cmd(&info->cmds, new);
		temp = info->arguments->head;
	}
	return (0);
}

int	print_args_deque(t_info *info)
{
	t_arg		*temp;
	
	temp = info->arguments->head;
	if (temp == NULL)
	{
		printf("arg_deque is empty\n");
	}
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
		return (0);
	}

	t_cmd	*temp_cmd;
	int		i;

	i = 0;
	temp_cmd = info->cmds;
	while (temp_cmd != NULL)
	{
		printf("\n---------------- < %d번째 command line >----------------\n");
		temp = temp_cmd->redirections;
		while (temp != NULL)
		{
			printf("type:%d | file: %s \n", temp->special, temp->arg);
			temp = temp->next;
		}
		i = 0;
		while (temp_cmd->commands_args[i] != NULL)
		{
			printf("arg[%d]: %s\n", i, temp_cmd->commands_args[i]);
			i++;
		}
		temp_cmd == temp_cmd->next;
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
