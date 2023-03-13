/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_devide_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:28 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/13 21:12:02 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_node_init(t_cmd	**node, t_arg_deque *args)
{
	t_arg	*temp;
	int		cmd_arg_count;
	int		redirect_flag;

	if (*node == NULL)
		return (ERROR);
	cmd_arg_count = 0;
	redirect_flag = 0;
	temp = args->head;
	while (temp != NULL)
	{
		if (temp->special == PIPE)
			break ;
		else if (temp->special == NONE)
			cmd_arg_count++;
		else
			redirect_flag++;
		temp = temp->next;
	}
	(*node)->commands_args = (char **)ft_calloc(sizeof(char *), cmd_arg_count + 1);
	if (redirect_flag > 0)
		(*node)->redirections = (t_arg_deque *)ft_calloc(sizeof(t_arg_deque), 1);
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
		while (info->arguments->head != NULL)
		{
			arg_node = pop_head_arg(&(info->arguments->head));
			if (arg_node->special == PIPE)
			{
				free(arg_node->arg);
				free(arg_node);
				break ;
			}
			else if (arg_node->special == NONE)
			{
				new->commands_args[i] = arg_node->arg;
				free(arg_node);
				i++;
			}
			else
			{
				free(arg_node->arg);
				arg_node->arg = info->arguments->head->arg;
				append_tail_arg(&(new->redirections), arg_node);
				arg_node = pop_head_arg(&(info->arguments->head));
				free(arg_node);
			}
		}
		append_tail_cmd(&info->cmds, new);
		temp = info->arguments->head;
	}
	free(info->arguments);
	return (0);
}

int	print_args_deque(t_info *info)
{
	t_arg		*temp;
	int			heredoc_flag;
	
	heredoc_flag = 0;
	temp = info->arguments->head;
	if (temp == NULL)
	{
		printf("arg_deque is empty\n");
	}
	while (temp != NULL)
	{
		if (temp->special == PIPE)
		{
			if (temp->next != NULL && temp->previous != NULL)
			{
				info->pipes += 1;
			}
			else
			{
				write(2, "minishell: syntax error near unexpected token `|'\n", 50);
				return (ERROR);
			}
		}
		else if (temp->special != 0 && (temp->next == NULL || temp->next->special != 0))
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, temp->arg, ft_strlen(temp->arg));
			write(2, "\'\n", 2);
			return (ERROR);
		}
		else if (temp->special == HEREDOC)
		{
			heredoc_flag++;
			if (heredoc_flag > 16)
			{
				write(2, "minishell: maximum here-document count exceeded\n", 48);
				exit(2);
			}
		}
		printf("----------------------\n\n[input]: %s\n[type]: %d\n\n----------------------\n", temp->arg, temp->special);
		temp = temp->next;
	}
	return (0);
}
