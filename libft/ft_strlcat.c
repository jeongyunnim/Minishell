/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:35:36 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/19 18:12:23 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	src_i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	src_i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_size <= dest_len)
		return (dest_size + src_len);
	while (dest[i] != '\0' && i + 1 < dest_size)
		i++;
	while (src[src_i] != '\0' && (i + src_i + 1) < dest_size)
	{
		dest[i + src_i] = src[src_i];
		src_i++;
	}
	if (dest_len < i + src_i)
		dest[i + src_i] = '\0';
	return (dest_len + src_len);
}
