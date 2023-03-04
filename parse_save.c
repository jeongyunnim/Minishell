/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/04 21:55:03 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	meet_meta_replace(char **input, char **arg)
{
	char	special;

	if (**input == '>' && *((*input) + 1) == '>')
	{
		ft_memcpy(*arg, ">>", 2);
		(*arg) += 2;
		(*input) += 2;
		return (APPEND);
	}
	else if (**input == '<' && *((*input) + 1) == '<')
	{
		ft_memcpy(*arg, "<<", 2);
		(*arg) += 2;
		(*input) += 2;
		return (HEREDOC);
	}
	else
	{
		ft_memcpy(*arg, *input, 1);
		special = **input;
		(*arg) += 1;
		(*input) += 1;
		return (special);
	}
}

int	save_arg(char **input, char *arg, int arg_len, t_env_deque *envs)
{
	char	special;
	char	quote_flag;

	quote_flag = 0;
	special = 0;
	while (**input != '\0')
	{
		if (quote_flag == 0 && ft_isspace(**input) == 1)
			return (special);
		else if (is_quote(**input) == 1)
			enter_quote(**input, &quote_flag);
		else if (quote_flag != 1 && **input == '$')
		{
			replace_env(input, &arg, envs, quote_flag);
            if (**input == '\0')
                return (special);
		}
		else if (quote_flag == 0 && ft_ismeta(**input) == 1)
		{
			special = meet_meta_replace(input, &arg);
			return (special);
		}
		else
		{
 			*arg = **input;
            arg++;
		}
		(*input)++;
		if (quote_flag == 0 && ft_ismeta(**input) == 1)
		{		
			return (special);
		}
	}
	return (special);
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
