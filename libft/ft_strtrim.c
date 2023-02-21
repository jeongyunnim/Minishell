/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:09:32 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/17 21:39:43 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trimed;
	char		*start;
	char		*end;

	if (s1 == 0 || set == 0)
		return (NULL);
	if (!ft_strlen(s1) || !ft_strlen(set))
		return (ft_strdup(s1));
	start = (char *)s1;
	end = (char *)start + ft_strlen(s1) - 1;
	while (*start != '\0' && ft_strchr(set, *start) != 0)
		start++;
	while (ft_strchr(set, *end) != 0)
	{
		if (end-- < start)
			break ;
	}
	if (end < start)
		return ((char *)ft_calloc(1, sizeof(char)));
	else
		trimed = (char *)ft_calloc(end - start + 2, sizeof(char));
	if (!trimed)
		return (NULL);
	else
		return (ft_memmove(trimed, start, end - start + 1));
}
