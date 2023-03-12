/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_cmd_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:38:31 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 14:52:48 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

void	append_head_cmd(t_cmd **head, t_cmd **tail, t_cmd *new)
{
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*head)->previous = new;
		new->next = *head;
		*head = new;
		(*head)->previous = NULL;
	}
}

void	append_tail_cmd(t_cmd **head, t_cmd **tail, t_cmd *new)
{
	if (*tail == NULL)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		new->previous = *tail;
		*tail = new;
		(*tail)->next = NULL;
	}
}
