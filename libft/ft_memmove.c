/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:26:22 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/22 14:51:43 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	size_t			i;

	c_dest = (unsigned char *)dest;
	c_src = (unsigned char *)src;
	if (c_dest == src || len == 0)
		return (dest);
	if (dest <= src)
	{
		i = -1;
		while (++i < len)
			c_dest[i] = c_src[i];
	}
	else
	{
		while (len > 0)
		{
			c_dest[len - 1] = c_src[len - 1];
			len--;
		}
	}
	return (dest);
}
