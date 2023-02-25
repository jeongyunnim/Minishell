/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/23 22:09:31 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_arg(char **input, char *arg, int arg_len, t_env_deque *envs)
{
	unsigned int	cnt;
	unsigned int	i;
	int				quote_flag;

	cnt = 0;
	i = 0;
	quote_flag = 0; // '(1)는 환경변수를 해석 안 함. "(2)는 환경변수 해석함
	while (**input != '\0')
	{
		if (**input == '\0')
		{
			break ;
		}
		if (quote_flag != 0)
		{
			if (quote_flag == 1)
			{
				if (**input == '\'')
				{
					quote_flag = 0;
				}
				else
				{
					*arg = **input;
					arg++;
				}
			}
			else if (quote_flag == 2)
			{
				if (**input == '\"')
				{
					quote_flag = 0;
				}
				else if (**input == '$')
				{
					(*input)++;
					//환경변수 가져오기.. + 환경변수 길이만큼 할당할 길이. 달러는 스킵.
				}
				else
				{
					*arg = **input;
					arg++;
				}
			}
		}
		else
		{
			if (ft_isspace(**input) != 0)
			{
				if (quote_flag != 0)
					return (ERROR);
				return (cnt);
			}
			else
			{
				if (ft_isspecial(**input) != 0)
				{
					if (**input == '\'')
					{
						quote_flag = 1;
					}
					else if (**input == '\"')
					{
						quote_flag = 2;
					}
					//특수문자 처리
				}
				else
				{
					*arg = **input;
					arg++;
				}
			}
		}
		// 특수문자 처리 (만약 $ 만나면, 환경변수 찾아서 처리해줘야 함. get_env 같은 놈)
		(*input)++;
	}
	*arg = '\0';
	return (0);
}

int	ft_isupper(char c)
{
	if ('A' <= c && c <= 'Z')
	{
		return (1);
	}
	else
		return (0);
}

int	replace_env(char **input, unsigned int i, t_env_deque *env)
{
	if (ft_isupper(*input[i]) == 0)
	{
		if (ft_isdigit(*input[i]) != 0)
		{
			i++;
		}
		else
		{
			while (*input[i] != '\0')
			{
				i++;
			}
		}
		return (i);
	}
	else
	{
		ft_strchr(*input, env->head->name)
	}
	return (0);
}

int	arg_to_deque(t_arg_deque **args, char *arg)
{
	t_arg	*new;

	new = lstnew_arg(arg);
	if (new == NULL)
	{
		return (ERROR);
	}
	append_tail_arg(&((*args)->head), &((*args)->tail), new);
	return (0);
}
