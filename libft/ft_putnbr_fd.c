/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:25:32 by jeseo             #+#    #+#             */
/*   Updated: 2022/07/31 17:17:51 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nbr(long long n, int fd)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, 1);
	}
	else
	{
		print_nbr(n / 10, fd);
		print_nbr(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	l_n;

	l_n = (long long)n;
	if (l_n < 0)
	{
		ft_putchar_fd('-', fd);
		l_n *= -1;
	}
	print_nbr(l_n, fd);
}
