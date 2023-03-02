/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/02 17:36:56 by jeseo            ###   ########.fr       */
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

int	quote_or_env_replace(char **input, char **arg, t_env_deque *envs, int *quote_flag)
{
	if (**input == '\'')
	{
		*quote_flag = 1;
	}
	else if (**input == '\"')
	{
		*quote_flag = 2;
	}
	else
	{
		(*input)++;
		if (replace_env(input, arg, envs))
			return (ERROR);
		(*input)--;
	}
	return (0);
}

int	save_arg(char **input, char *arg, int arg_len, t_env_deque *envs)
{
	int	special;
	int	quote_flag;

	quote_flag = 0; // '(1)는 환경변수를 해석 안 함. "(2)는 환경변수 해석함
	special = 0;
	while (**input != '\0')
	{
		if (quote_flag != 0)
		{
			inside_quote_replace(input, &arg, envs, &quote_flag);
			if (quote_flag == 0 && ft_isspecial_symbol(*((*input) + 1)) == 1)
			{
				*arg = **input;
				arg++;
				(*input)++;
				return (0);
			}
		}
		else
		{
			if (ft_isspace(**input) == 1)
			{
				return (NONE);
			}
			else if (is_quote_or_env(**input) == 1)
			{
				if (quote_or_env_replace(input, &arg, envs, &quote_flag) == ERROR)
					return (ERROR);
			}
			else if (ft_isspecial_symbol(**input) == 1)
			{
				if (**input == '>' && *((*input) + 1) == '>')
				{
					ft_memcpy(arg, ">>", 2);
					arg += 2;
					(*input) += 2;
					return (APPEND);
				}
				else if (**input == '<' && *((*input) + 1) == '<')
				{
					ft_memcpy(arg, "<<", 2);
					arg += 2;
					(*input) += 2;
					return (HEREDOC);
				}
				else
				{
					ft_memcpy(arg, *input, 1);
					arg += 1;
					special = **input;
					(*input) += 1;
					return (special);
				}
			}
			else if (ft_isspecial_symbol(*((*input) + 1)) == 1)
			{
				*arg = **input;
				arg++;
				(*input)++;
				return (0);
			}
			else
			{
				*arg = **input;
                arg++;
			}
		}
		(*input)++;
	}
	*arg = '\0';//어차피 calloc이라 안해줘도 같을 것 같다.
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

int	arg_to_deque(t_arg_deque **args, char *arg, int	special)
{
	t_arg	*new;

	new = lstnew_arg(arg);
	if (new == NULL)
	{
		return (ERROR);
	}
	new->special = special;
	append_tail_arg(&((*args)->head), &((*args)->tail), new);
	return (0);
}
