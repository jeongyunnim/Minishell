/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/22 21:40:49 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg_len(char *input)
{
	unsigned int	cnt;
	int				quote_flag;

	cnt = 0;
	quote_flag = 0; // '(1)는 환경변수를 해석 안 함. "(2)는 환경변수 해석함
	while (*input != '\0')
	{
		if (*input == '\0')
		{
			return (cnt);
		}
		else if (quote_flag == 0 && ft_isspace(*input) == 0)
		{
			return (cnt);
		}
		else if (*input == '\'' && quote_flag == 0)
		{
			quote_flag = 1; // 문자로 보겠다.
		}
		else if (*input == '\"' && quote_flag == 0)
		{
			quote_flag = 2; // 환경변수를 처리하겠다.
		}
		else if (*input == '\'' && quote_flag == 1)
		{
			quote_flag = 0;
		}
		else if (*input == '\"' && quote_flag == 2)
		{
			quote_flag = 0;
		}
		// 만약 $ 만나면, 환경변수 찾아서 처리해줘야 함. get_env 같은 놈.
		else
		{
			cnt++;
			if (cnt >= INT_MAX)
			{
				write(2, "Minishell: Argument too long\n", 29);
				return (ERROR);
			}
		}
		input++;
	}
	return (cnt);
}

int	parse(char *input)
{
	t_deque	*args;
	char	*arg;
	int		arg_len;

	args = (t_deque *)ft_calloc(1, sizeof(t_deque));
	if (args == NULL)
		return (ERROR);
	while (*input != '\0')
	{
		//while (ft_isspace(*input) == 0)
		//	input++;
		if (*input != '\0')
		{
			arg_len = count_arg_len(input);
			if (arg_len == -1)
				return (ERROR);
			else
			{
				arg = (char *)ft_calloc(arg_len + 1, sizeof(char));
				if (arg == NULL)
					return (ERROR);
			}
			save_arg(&input, arg, arg_len);
			arg_to_deque(&args, arg);
		}
	}
	
	/* 잘 담겼는지 확인하기 */
	t_node *tmp;
	tmp = args->head;
	while(tmp != NULL)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
	while(args->head != NULL)
	{
		tmp = pop_head(&args->head);
		free(tmp->arg);
		free(tmp);
	}
	return (0);
}