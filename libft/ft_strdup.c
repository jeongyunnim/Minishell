/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:58:39 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/12 20:11:01 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		str_len;
	char	*str_dup;

	i = 0;
	str_len = ft_strlen(str);
	str_dup = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str_dup == NULL)
		exit(EXIT_FAILURE);
	while (i < str_len)
	{
		str_dup[i] = str[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
