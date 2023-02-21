/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:33:18 by jeseo             #+#    #+#             */
/*   Updated: 2022/09/06 19:18:23 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	while (src[i] != '\0' && i + 1 < dest_size)
	{
		dest[i] = src[i];
		i++;
	}
	if (dest_size > 0)
		dest[i] = '\0';
	return (src_size);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char dest[5];
// 	ft_strlcpy(dest, "aaa", 0);
// 	printf("|%s|\n", dest);
// 	strlcpy(dest, "aaa", 0);	
// 	printf("|%s|\n", dest);

// 	return (0);
// }