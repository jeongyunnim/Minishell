/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_cmd_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:38:31 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*lstnew_cmd(void)
{
	t_cmd	*link;

	link = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (link == NULL)
		return (NULL);
	return (link);
}

t_cmd	*pop_head_cmd(t_cmd **head)
{
	t_cmd	*pop;

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

t_cmd	*pop_tail_cmd(t_cmd **tail)
{
	t_cmd	*pop;

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

void	append_head_cmd(t_cmd_deque **deque, t_cmd *new)
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

void	append_tail_cmd(t_cmd_deque **deque, t_cmd *new)
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
