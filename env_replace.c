/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:45:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/28 17:42:22 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	special_parameter_len(char *input, unsigned int *cnt)
{
	if (*input == '0')
	{
		*cnt += 9;
	}
	else if (*input == '?')
	{
		if (0 <= g_exit_code && g_exit_code < 10)
            *cnt += 1;
        else if (10<= g_exit_code && g_exit_code < 100)
            *cnt += 2;
        else
            *cnt += 3;
	}
	return (1);
}

int	special_parameter_replace(char **input, char **arg)
{
	char	*code;

	if (**input == '0')
	{
		(*input)++;
		ft_memcpy(*arg, "minishell", 9);
		(*arg) += 9;
	}
	else if (**input == '?')
	{
		(*input)++;
		code = ft_itoa(g_exit_code);
		if (code == NULL)
		{
			printf("설마하니 itoa 할당이 실패하겠어?\n");
			//이토아 실패 어떤 메세지를 출력해야 할까?
			return (ERROR);
		}
		ft_memcpy(*arg, code, ft_strlen(code));
		(*arg) += ft_strlen(code);
		free(code);
	}
	return (0);
}