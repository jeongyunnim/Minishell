/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_deque.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:45:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/22 21:31:37 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	save_arg(char **input, char *arg, int arg_len)
{
	if (arg_len == 0)
		return ;
	if (**input == '\'' || **input == '\"')
		(*input)++;
	while (arg_len > 0)
	{
		*arg = **input;
		arg++;
		(*input)++;
		arg_len--;
	}
	*arg = '\0';
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