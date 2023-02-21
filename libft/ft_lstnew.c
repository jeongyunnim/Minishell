/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:23:58 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/17 21:41:40 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*link;

	link = (t_list *)malloc(1 * sizeof(t_list));
	if (link == NULL)
		return (NULL);
	link -> content = content;
	link -> next = NULL;
	return (link);
}
