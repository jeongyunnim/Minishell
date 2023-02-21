/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:40:12 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/17 21:41:22 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new || !lst)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		*lst = new;
		new -> next = temp;
	}
}
