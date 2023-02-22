/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 21:49:25 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/22 20:23:04 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_node	*lstnew(char *arg)
{
	t_node	*link;

	link = (t_node *)ft_calloc(1, sizeof(t_node));
	if (link == NULL)
		return (NULL);
	link->arg = ft_strdup(arg);
	if (link->arg == NULL)
		return (NULL);
	return (link);
}

t_node	*pop_head(t_node **head)
{
	t_node	*pop;

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

t_node	*pop_tail(t_node **tail)
{
	t_node	*pop;

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

void	append_head(t_node **head, t_node **tail, t_node *new)
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

void	append_tail(t_node **head, t_node **tail, t_node *new)
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
