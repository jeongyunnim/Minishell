/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:49:25 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/21 21:54:53 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_deque	*lstnew(char *arg)
{
	t_deque	*link;

	link = (t_deque *)malloc(1 * sizeof(t_deque));
	if (link == NULL)
		return (NULL);
	link->args = ft_strdup(arg);
	if (link->args == NULL)
		return (NULL);
	link->previous = NULL;
	link->next = NULL;
	return (link);
}

t_deque	*pop_head(t_deque **head)
{
	t_deque	*pop;

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

t_deque	*pop_tail(t_deque **tail)
{
	t_deque	*pop;

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

void	append_head(t_deque **head, t_deque **tail, t_deque *new)
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

void	append_tail(t_deque **head, t_deque **tail, t_deque *new)
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
