/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:03:14 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/20 14:31:00 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *bytes, int value, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)bytes;
	while (len > 0)
	{
		*temp = value;
		temp++;
		len--;
	}
	return (bytes);
}
