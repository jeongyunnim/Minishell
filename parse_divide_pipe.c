/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_divide_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 18:02:28 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/20 20:52:03 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	cmd_node_init(t_cmd	**node, t_arg_deque *args)
{
	t_arg	*temp;
	int		cmd_arg_count;
	int		redirect_flag;

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
	(*node)->commands_args = ft_calloc(sizeof(char *), cmd_arg_count + 1);
	if (redirect_flag > 0)
		(*node)->redirections = ft_calloc(sizeof(t_arg_deque), 1);
	return (0);
}

int	argument_to_cmd(t_info	*info, )
{
	t_arg	*arg_node;
	
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

int divide_pipe(t_info	*info)
{
	t_arg	*temp;
	t_cmd	*new;
	int		i;

	info->cmds = ft_calloc(sizeof(t_cmd_deque), 1);
	temp = info->arguments->head;
	while (temp != NULL)
	{
		new = lstnew_cmd();
		cmd_node_init(&new, info->arguments);
		i = 0;
		while (info->arguments->head != NULL)
		{
		}
		append_tail_cmd(&info->cmds, new);
		temp = info->arguments->head;
	}
	free(info->arguments);
	return (0);
}

static int	is_valid_pipe(t_arg *temp)
{
	if (temp->next == NULL || temp->previous == NULL)
	{
		print_error(SYNTAX_ERROR, temp->arg);
		return (0);
	}
	return (1);
}

static int	is_valid_special(t_arg *temp)
{
	if (temp->next == NULL || temp->next->special != 0)
	{
		print_error(SYNTAX_ERROR, temp->arg);
		return (0);
	}
	return (1);
}

int	args_check(t_info *info)
{
	t_arg	*temp;
	int		heredoc_flag;

	heredoc_flag = 0;
	temp = info->arguments->head;
	while (temp != NULL)
	{
		if (temp->special == PIPE)
		{
			if (is_valid_pipe(temp) == 0)
				return (ERROR);
			info->pipes += 1;
		}
		else if (temp->special != 0 && is_valid_special(temp) == NULL)
			return (ERROR);
		else if (temp->special == HEREDOC)
			heredoc_flag++;
		temp = temp->next;
	}
	if (heredoc_flag > 16)
		print_error(HEREDOC_MAX_ERROR, NULL);
	return (0);
}
