/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:08 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/04 18:05:36 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_quote_cnt(char *input, t_env_deque *env, unsigned int *cnt, int *quote_flag)
{
	unsigned int	i;

	i = 0;
	if (*quote_flag == 1)
	{
		if (input[i] == '\'')
		{
			*quote_flag = 0;
		}
		else
		{
			(*cnt)++;
		}
	}
	else if (*quote_flag == 2)
	{
		if (input[i] == '\"')
		{
			*quote_flag = 0;
		}
		else if (input[i] == '$')
		{
			i++;
			i += set_env_len(&input[i], cnt, env);
			return (i - 1);
		}
		else
		{
			(*cnt)++;
		}
	}
	return (i);
}

void	enter_quote(char input, int *quote_flag)
{
	if (input == '\'')
		*quote_flag = 1;
	else if (input == '\"')
		*quote_flag = 2;
}

void	meet_meta_cnt(char *input, unsigned int *cnt)
{
	if (*input == '>' && *(input + 1) == '>')
	{
		*cnt += 2;
	}
	else if (*input == '<' && *(input + 1) == '<')
	{
		*cnt += 2;
	}
	else
	{
		*cnt += 1;
	}
}

