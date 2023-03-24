/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:16:44 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/25 04:40:54 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_pipe(t_arg *temp)
{
	if (temp->next == NULL || temp->previous == NULL)
	{
		g_exit_code = 258;
		print_error(SYNTAX_ERROR, temp->arg);
		return (0);
	}
	return (1);
}

static int	is_valid_special(t_arg *temp)
{
	t_arg	*next;

	next = temp->next;
	if (next == NULL || next->special != 0)
	{
		if (next->special == NO_ENV)
		{
			g_exit_code = 258;
			print_error(SYNTAX_ERROR, temp->arg);
		}
		else
		{
			g_exit_code = 1;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("ambiguous redirect\n", 2);
		}
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
		else if ((temp->special != NONE && temp->special != NO_ENV) \
					&& is_valid_special(temp) == 0)
			return (ERROR);
		else if (temp->special == HEREDOC)
			heredoc_flag++;
		temp = temp->next;
	}
	if (heredoc_flag > 16)
		print_error(HEREDOC_MAX_ERROR, NULL);
	return (0);
}
