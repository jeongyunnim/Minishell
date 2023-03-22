/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 19:45:54 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/22 19:24:30 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	env_special_len(char *input)
{
	int	cnt;

	if (*input == '0')
	{
		return (9);
	}
	else if (*input == '?')
	{
		if (g_exit_code < 10)
			return (1);
		else if (g_exit_code < 100)
			return (2);
		else
			return (3);
	}
	else
	{
		return (2);
	}
}

int	env_special_replace(char **input, char **arg)
{
	char	*code;

	if (**input == '0')
	{
		ft_memcpy(*arg, "minishell", 9);
		(*arg) += 9;
		(*input)++;
	}
	else if (**input == '?')
	{
		code = ft_itoa(g_exit_code);
		ft_memcpy(*arg, code, ft_strlen(code));
		*arg += ft_strlen(code);
		free(code);
		(*input)++;
	}
	else
	{
		ft_memcpy(*arg, "$$", 2);
		*arg += 2;
		(*input)++;
	}
	return (0);
}

void	replace_env(char **input, char **arg, t_env_deque *env, char qflag)
{
	unsigned int	i;

	i = 0;
	(*input)++;
	if (**input == '\0' || ft_isspace(**input) == 1 \
	|| (is_quote(**input) == 1 && qflag != 0))
	{
		**arg = '$';
		(*arg)++;
	}
	else if (is_quote(**input) == 1)
		(*input)++;
	else if (ft_isalpha(**input) || is_env_special(**input) || **input == '_')
		valid_env_name_replace(input, arg, env);
	else
	{
		if (invalid_env_name(*input, &i) == 1)
		{
			**arg = '$';
			(*arg)++;
		}
		(*input) += i;
	}
	(*input)--;
}

int	set_env_len(char *input, unsigned int *i, t_env_deque *env, char qflag)
{
	int	cnt;

	cnt = 0;
	(*i)++;
	if (input[*i] == '\0' || ft_isspace(input[*i]) == 1 \
		|| (is_quote(input[*i]) == 1 && qflag != 0))
		return (1);
	else if (is_quote(input[*i]) == 1)
		return (0);
	if (ft_isalpha(input[*i]) || is_env_special(input[*i]) || input[*i] == '_')
	{
		cnt = valid_env_name_match(input, env, i);
		return (cnt);
	}
	else
	{
		if (invalid_env_name(input, i) == 1)
			return (1);
		return (0);
	}
}
