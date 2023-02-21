/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:48:18 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/17 21:16:39 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp1;
	t_list	*temp2;

	if (lst == NULL || del == NULL)
		return ;
	temp1 = *lst;
	while (temp1)
	{
		temp2 = temp1 -> next;
		del(temp1 -> content);
		free(temp1);
		temp1 = temp2;
	}
	*lst = NULL;
}
