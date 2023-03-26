/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_arg_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:49:25 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:16:37 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	*lstnew_arg(char *arg)
{
	t_arg	*link;

	link = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (link == NULL)
		return (NULL);
	link->arg = ft_strdup(arg);
	if (link->arg == NULL)
		return (NULL);
	return (link);
}

t_arg	*pop_head_arg(t_arg **head)
{
	t_arg	*pop;

	pop = *head;
	if (pop == NULL)
		return (NULL);
	if ((*head)->next != NULL)
	{
		*head = (*head)->next;
		(*head)->previous = NULL;
	}
	else
	{
		*head = NULL;
	}
	pop->next = NULL;
	pop->previous = NULL;
	return (pop);
}

t_arg	*pop_tail_arg(t_arg **tail)
{
	t_arg	*pop;

	pop = *tail;
	if (pop == NULL)
		return (NULL);
	if ((*tail)->previous != NULL)
	{
		*tail = (*tail)->previous;
		(*tail)->next = NULL;
	}
	else
	{
		*tail = NULL;
	}
	pop->next = NULL;
	pop->previous = NULL;
	return (pop);
}

void	append_head_arg(t_arg_deque **deque, t_arg *new)
{
	if ((*deque)->head == NULL)
	{
		(*deque)->head = new;
		(*deque)->tail = new;
	}
	else
	{
		(*deque)->head->previous = new;
		new->next = (*deque)->head;
		(*deque)->head = new;
		(*deque)->head->previous = NULL;
	}
}

void	append_tail_arg(t_arg_deque **deque, t_arg *new)
{
	if ((*deque)->tail == NULL)
	{
		(*deque)->head = new;
		(*deque)->tail = new;
	}
	else
	{
		(*deque)->tail->next = new;
		new->previous = (*deque)->tail;
		(*deque)->tail = new;
		(*deque)->tail->next = NULL;
	}
}
