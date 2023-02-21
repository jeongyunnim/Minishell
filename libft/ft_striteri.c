/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:44:02 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/31 16:45:56 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (s == 0)
		return ;
	while (i < s_len)
	{
		f(i, &s[i]);
		i++;
	}
}
