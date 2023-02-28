/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/28 20:43:41 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inside_quote_replace(char **input, char **arg, t_env_deque *envs, int *quote_flag)
{
	if (*quote_flag == 1)
	{
		if (**input == '\'')
		{
			*quote_flag = 0;
		}
		else
		{
			**arg = **input;
			(*arg)++;
		}
	}
	else if (*quote_flag == 2)
	{
		if (**input == '\"')
		{
			*quote_flag = 0;
		}
		else if (**input == '$')
		{
			(*input)++;
			replace_env(input, arg, envs);
			(*input)--;
		}
		else
		{
			**arg = **input;
			(*arg)++;
		}
	}
}

void	outside_quote_replace(char **input, char **arg, t_env_deque *envs, int *quote_flag)
{
	if (ft_isspecial(**input) != 0)
	{
		if (**input == '\'')
		{
			*quote_flag = 1;
		}
		else if (**input == '\"')
		{
			*quote_flag = 2;
		}
		else if (**input == '$')
		{
			(*input)++;
			replace_env(input, arg, envs);
			(*input)--;
		}
	}
    else
    {
        **arg = **input;
        (*arg)++;
    }
}

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
		if (quote_flag != 0)
		{
			inside_quote_replace(input, &arg, envs, &quote_flag);
		}
		else
		{
			if (ft_isspace(**input) != 0)
			{
				return (cnt);
			}
			else
			{
				outside_quote_replace(input, &arg, envs, &quote_flag);
			}
		}
		(*input)++;
	}
	*arg = '\0';
	return (0);
}

int	ft_isupper(int c)
{
	if ('A' <= c && c <= 'Z')
	{
		return (1);
	}
	else
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
