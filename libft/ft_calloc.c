/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:30:19 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 19:00:42 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	p = (void *)malloc(n * size);
	if (p == NULL)
	{
		ft_putstr_fd("malloc: Cannot allocate memory\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(p, n * size);
	return (p);
}
