/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:08 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/04 21:54:05 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enter_quote(char input, char *quote_flag)
{
	if (input == '\'' && *quote_flag != 2)
	{
		if (*quote_flag == 0)
			*quote_flag = 1;
		else
			*quote_flag = 0;
		return (0);
	}
	else if (input == '\"' && *quote_flag != 1)
	{
		if (*quote_flag == 0)
			*quote_flag = 2;
		else
			*quote_flag = 0;
		return (0);
	}
	else
		return (1);
}

int	meta_len(char *input)
{
	if (*input == '>' && *(input + 1) == '>')
	{
		return (2);
	}
	else if (*input == '<' && *(input + 1) == '<')
	{
		return (2);
	}
	else
	{
		return (1);
	}
}

 