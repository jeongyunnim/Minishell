/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:21:08 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_only_white_space(char *input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (input[i] != '\0')
	{
		if (ft_isspace(input[i]) == 0)
		{
			flag = 0;
			break ;
		}
		i++;
	}
	return (flag);
}

int	enter_quote(char input, char *quote_flag)
{
	if (input == '\'' && *quote_flag != 2)
	{
		if (*quote_flag == 0)
			*quote_flag = 1;
		else
			*quote_flag = 0;
		return (0);
	}
	else if (input == '\"' && *quote_flag != 1)
	{
		if (*quote_flag == 0)
			*quote_flag = 2;
		else
			*quote_flag = 0;
		return (0);
	}
	else
		return (1);
}

int	meta_len(char *input)
{
	if (*input == '>' && *(input + 1) == '>')
	{
		return (2);
	}
	else if (*input == '<' && *(input + 1) == '<')
	{
		return (2);
	}
	else
	{
		return (1);
	}
}

int	count_arg_len(char *input, t_parse_index index, t_env_deque *envs)
{
	while (input[index.i] != '\0')
	{
		if (index.quote_flag == 0 && ft_isspace(input[index.i]) == 1)
			return (index.cnt);
		else if (is_quote(input[index.i]) == 1)
			index.cnt += enter_quote(input[index.i], &index.quote_flag);
		else if (index.quote_flag != 1 && input[index.i] == '$')
		{
			index.cnt += set_env_len(input, &index.i, envs, index.quote_flag);
			(index.i)--;
		}
		else if (index.quote_flag == 0 && is_meta(input[index.i]) == 1)
			return (meta_len(input));
		else
			(index.cnt)++;
		if (input[index.i] != '\0')
			(index.i)++;
		if (index.quote_flag == 0 && is_meta(input[index.i]) == 1)
			return (index.cnt);
	}
	if (index.quote_flag != 0)
		return (QUOTE_ERROR);
	return (index.cnt);
}
