/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:16:11 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/19 12:39:45 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*temp;
	char	c_char;

	temp = 0;
	c_char = (char) c;
	while (*str != '\0')
	{
		if (*str == c_char)
			temp = (char *)str;
		str++;
	}
	if (*str == c_char)
		return ((char *)str);
	return (temp);
}
