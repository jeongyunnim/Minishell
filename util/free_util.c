/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:34:51 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_node(t_cmd **cmd_node)
{
	char	*args;
	int		i;

	if (*cmd_node == NULL)
		return ;
	if ((*cmd_node)->redirections != NULL)
	{
		free_arg_deque(&((*cmd_node)->redirections));
	}
	if ((*cmd_node)->cmd_args != NULL)
	{
		i = 0;
		args = (*cmd_node)->cmd_args[i];
		while (args != NULL)
		{
			free(args);
			i++;
			args = (*cmd_node)->cmd_args[i];
		}
		free((*cmd_node)->cmd_args);
	}
	free(*cmd_node);
}

void	free_arg_deque(t_arg_deque **arg_deque)
{
	t_arg	*arg_node;

	if (*arg_deque == NULL)
		return ;
	arg_node = pop_head_arg(&((*arg_deque)->head));
	while (arg_node != NULL)
	{
		free(arg_node->arg);
		free(arg_node);
		arg_node = pop_head_arg(&((*arg_deque)->head));
	}
	free(*arg_deque);
}

void	free_env_deque(t_env_deque **env_deque)
{
	t_env	*env_node;

	if (*env_deque == NULL)
		return ;
	env_node = pop_head_env(&((*env_deque)->head));
	while (env_node != NULL)
	{
		if (env_node->name != NULL)
			free(env_node->name);
		if (env_node->value != NULL)
			free(env_node->value);
		free(env_node);
		env_node = pop_head_env(&((*env_deque)->head));
	}
	free(*env_deque);
}
