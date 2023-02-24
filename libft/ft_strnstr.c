/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:08:09 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/20 14:31:06 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *dest, const char *src, size_t n)
{
	size_t	s_len;

	s_len = ft_strlen(src);
	if (*src == '\0')
		return ((char *) dest);
	while (*dest != '\0' && s_len <= n && n > 0)
	{
		if (*dest == *src)
		{
			if (ft_strncmp((char *)dest, (char *)src, s_len) == 0)
				return ((char *) dest);
		}
		dest++;
		n--;
	}
	return (0);
}
