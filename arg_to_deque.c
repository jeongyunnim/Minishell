/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_deque.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:45:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/23 18:18:14 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	save_arg(char **input, char *arg, int arg_len)
{
	int	quote_flag;

	quote_flag = 0;
	if (arg_len == 0)
		return (NONE);
	if (**input == '\'' || **input == '\"')
	{
		quote_flag = 1;
		(*input)++;
	}
	while (arg_len > 0)
	{
		*arg = **input;
		arg++;
		(*input)++;
		arg_len--;
	}
	*arg = '\0';
	return (NONE);
}

int	arg_to_deque(t_deque **args, char *arg)
{
	t_node	*new;

	new = lstnew(arg);
	if (new == NULL)
	{
		return (ERROR);
	}
	append_tail(&(*args)->head, &(*args)->tail, new);
	return (0);
}