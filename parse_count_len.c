/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:08 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/28 19:07:48 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inside_quote(char *input, t_env_deque *env, unsigned int *cnt, int *quote_flag)
{
	unsigned int	len;

	len = 0;
	if (*quote_flag == 1)
	{
		if (*input == '\'')
		{
			*quote_flag = 0;
		}
		else
		{
			(*cnt)++;
		}
	}
	else
	{
		if (*input == '\"')
		{
			*quote_flag = 0;
		}
		else if (*input == '$')
		{
			len = set_env_len(input, cnt, env);
			return (len - 1); // i 지우고 반환 값을 i로 건네주도록 하자.
			//환경변수 가져오기.. + 환경변수 길이만큼 할당할 길이. 달러는 스킵.
		}
		else
		{
			(*cnt)++;
		}
	}
	return (len);
}