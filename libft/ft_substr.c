/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:05:55 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/22 17:18:00 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	chk_size(const char *s, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (len < s_len)
		return (len);
	else
		return (s_len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	size_t	s_len;
	char	*sub;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (s_len < start)
		return ((char *)ft_calloc(1, sizeof(char)));
	size = chk_size(s + start, len);
	sub = (char *)ft_calloc(size + 1, sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		sub[i++] = s[start++];
	return (sub);
}
