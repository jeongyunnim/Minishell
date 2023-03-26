/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	save_arg(char **input, char *arg, t_env_deque *envs)
{
	char	quote_flag;

	quote_flag = 0;
	while (**input != '\0')
	{
		if (quote_flag == 0 && ft_isspace(**input) == 1)
			return (0);
		else if (is_quote(**input) == 1)
		{
			if (enter_quote(**input, &quote_flag) == 1)
				*(arg++) = **input;
		}
		else if (quote_flag != 1 && **input == '$')
			replace_env(input, &arg, envs, quote_flag);
		else if (quote_flag == 0 && is_meta(**input) == 1)
			return (meet_meta_replace(input, &arg));
		else
			*(arg++) = **input;
		if (**input != '\0')
			(*input)++;
		if (quote_flag == 0 && is_meta(**input) == 1)
			return (0);
	}
	return (0);
}

int	arg_to_deque(t_arg_deque **args, char *arg, int special)
{
	t_arg	*new;

	new = lstnew_arg(arg);
	new->special = special;
	append_tail_arg(args, new);
	return (0);
}
