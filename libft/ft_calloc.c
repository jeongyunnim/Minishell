/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:30:19 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 19:57:14 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	p = (void *)malloc(n * size);
	if (p == NULL)
	{
		write(2, "Insufficient memory\n", 20);
		exit(EXIT_FAILURE);
	}
	ft_bzero(p, n * size);
	return (p);
}
