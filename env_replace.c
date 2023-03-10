/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:45:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/05 15:50:07 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	env_special_len(char *input)
{
	int	cnt;
	
	if (*input == '0')
	{
		return (9);
	}
	else
	{
		if (g_exit_code < 10)
            return (1);
        else if (g_exit_code < 100)
            return (2);
        else
            return (3);
	}
}
void	code_to_arg(char (*code)[4])
{
	char	temp;
	int		i;

	temp = g_exit_code;
	i = 0;
	while (temp > 0)
	{
		temp /= 10;
		i++;
	}
	temp = g_exit_code;
	if (temp == 0)
		i++;
	while (i > 0)
	{
		*(code[i - 1]) = temp % 10 + '0';
		temp /= 10;
		i--;
	}
}

int	env_special_replace(char **input, char **arg)
{
	char	code[4];
	int		len;

	if (**input == '0')
	{
		ft_memcpy(*arg, "minishell", 9);
		(*arg) += 9;
	}
	else if (**input == '?')
	{
		ft_memset(code, 0, 4);
		code_to_arg(&code);
		if (g_exit_code < 10)
			len = 1;
		else if (g_exit_code < 100)
			len = 2;
		else
			len = 3;
		ft_memcpy(*arg, code, len);
		*arg += len;
	}
	(*input)++;
	return (0);
}