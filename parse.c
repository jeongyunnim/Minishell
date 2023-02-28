/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/28 20:37:56 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspecial(int c)
{
	if(c == '|' || c == '>' || c == '>' || c == '<' || c == '\'' || c == '\"' || c == '$')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	count_arg_len(char *input, t_env_deque *envs)
{
	unsigned int	cnt;
	unsigned int	i;
	int				quote_flag;

	cnt = 0;
	i = 0;
	quote_flag = 0; // '(1)는 환경변수를 해석 안 함. "(2)는 환경변수 해석함
	while (input[i] != '\0')
	{
		if (quote_flag != 0)
		{
			i += inside_quote(&input[i], envs, &cnt, &quote_flag);
		}
		else
		{
			if (ft_isspace(input[i]) == 1)
			{
				//if (quote_flag != 0)
				//{
				//	printf("쿼트가 아니면 뭐니 %d\n", input[i]);
				//	return (ERROR);
				//}
				//생각해보니 이쪽으로 쿼트가 올 리가 없는 듯 하다.
				return (cnt);
			}
			else
			{
				i += outside_quote(&input[i], envs, &cnt, &quote_flag);
			}
		}
		i++;
	}
	if (cnt >= INT_MAX)
	{
		write(2, "Minishell: Argument too long\n", 29);
		return (ERROR);
	}
	if(quote_flag != 0)
	{
		printf("syntax error: 쿼트가 닫히지 않음\n");
		return (ERROR);
	}
	return (cnt);
}

int	parse(char *input, t_info *info)
{
	t_arg_deque	*args;
	char		*arg;
	int			arg_len;

	// t_env	*tmp;
	// tmp = info->envs->head;
	// while (tmp != NULL)
	// {
	// 	printf("%s=%s\n", tmp->name, tmp->value);
	// 	tmp = tmp->next;
	// }

	args = (t_arg_deque *)ft_calloc(1, sizeof(t_arg_deque));
	if (args == NULL)
		return (ERROR);
	info->arguments = args;
	while (*input != '\0')
	{
		while (*input != '\0' && ft_isspace(*input) != 0)
		{
			input++;
		}
		if (*input != '\0')
		{
			arg_len = count_arg_len(input, info->envs);
			if (arg_len == -1)
				return (ERROR);
			else
			{
				arg = (char *)ft_calloc(arg_len + 1, sizeof(char));
				if (arg == NULL)
					return (ERROR);
			}
			save_arg(&input, arg, arg_len, info->envs);
			arg_to_deque(&args, arg);
		}
	}
	
	/* 잘 담겼는지 확인하기 */
	t_arg *tmp_arg;
	tmp_arg = args->head;
	while(tmp_arg != NULL)
	{
		printf("%s %ld\n", tmp_arg->arg, ft_strlen(tmp_arg->arg));
		tmp_arg = tmp_arg->next;
	}
	while(args->head != NULL)
	{
		tmp_arg = pop_head_arg(&args->head);
		free(tmp_arg->arg);
		free(tmp_arg);
	}
	return (0);
}