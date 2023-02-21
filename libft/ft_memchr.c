/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:09:33 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/19 13:11:29 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	u_c;

	temp = (unsigned char *)s;
	u_c = (unsigned char) c;
	while (n > 0)
	{
		if (*temp == u_c)
			return (temp);
		temp++;
		n--;
	}
	return (0);
}
