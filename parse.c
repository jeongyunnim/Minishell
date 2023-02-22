/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/22 18:16:25 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg_len(char *input)
{
	unsigned int	cnt;
	int				quote_flag;
	int				dquote_flag;

	cnt == 0;
	while (*input != '\0')
	{
		if (*input == '\0')
			return (cnt);
		else if (ft_isspace(*input))
			return (cnt);
		else
		{
			cnt++;
			if (cnt >= INT_MAX)
			{
				wrtie(2, "Minishell: Argument too long\n", 29);
				return (ERROR);
			}
		}
		input++;
	}
}

int	parse(char *input)
{
	t_deque	*args;
	char	*arg;

	args = (t_deque *)ft_calloc(1, sizeof(t_deque));
	if (args == NULL)
		return (ERROR);
	while (*input != '\0')
	{
		while (ft_isspace(*input) == 0)
			input++;
		if (*input != '\0')
			count_arg_len(input);
			
	}
	printf("%s\n", input);
	// 모든 화이트 스페이스를 건너 뛰어야 한다.
	/*
		1. input 받아온 것 white space 기준으로 모두 스플릿 한다.
		2. 각각의 인풋을 토큰화하기.
		3. 따옴표와 쌍따옴표를 체크해야한다.
		4. |가 문자 파이프인지 구분해야한다.
	*/
	return (0);
}