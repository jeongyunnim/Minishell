/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/03 20:50:18 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote_or_env(int c)
{
	if(c == '\'' || c == '\"' || c == '$')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_ismeta(int c)
{
	if(c == '>' || c == '<' || c == '|')
	{
		return (1);
	}
	else
	{~
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
	quote_flag = 0;
	while (input[i] != '\0')
	{
		if (quote_flag != 0)
		{
			i += inside_quote_cnt(&input[i], envs, &cnt, &quote_flag);
			if (quote_flag == 0 && ft_ismeta(input[i + 1]) == 1)
			{
				return (cnt);
			}
		}
		else
		{
			if (ft_isspace(input[i]) == 1)
			{
				return (cnt);
			}
			else if (is_quote_or_env(input[i]))
			{
				i += quote_and_env_cnt(&input[i], envs, &cnt, &quote_flag); // quote 와 $ 분리하자.
			}
			else if (ft_ismeta(input[i]) == 1)
			{
				if (input[i] == '>' && input[i + 1] == '>')
				{
					cnt += 2;
				}
				else if (input[i] == '<' && input[i] == '<')
				{
					cnt += 2;
				}
				else
				{
					cnt++;
				}
				return (cnt);
			}
			else if (ft_ismeta(input[i + 1]) == 1)
			{
				cnt++;
				//input[i]는 일반문자이므로 ls|에서 s를 가리키고 있어야 함.
				return (cnt);
			}
			else
			{
				cnt++;
			}
		}
		i++;
	}
	if (cnt >= INT_MAX)
	{
		write(2, "minishell: Argument too long\n", 29);
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
	int			special;

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
		special = 0;
		while (*input != '\0' && ft_isspace(*input) != 0)
		{
			input++;
		}
		if (*input != '\0')
		{
			arg_len = count_arg_len(input, info->envs);
			if (arg_len == ERROR)
			{

				return (ERROR);
			}
			else
			{
				arg = (char *)ft_calloc(arg_len + 1, sizeof(char));
				if (arg == NULL)
					return (ERROR);
			}
			special = save_arg(&input, arg, arg_len, info->envs);
			if (special == ERROR)
			{
				return (ERROR);
			}
			arg_to_deque(&args, arg, special);
		}
	}
	
	/* 잘 담겼는지 확인하기 */
	//t_arg *tmp_arg;
	//tmp_arg = args->head;
	//while(tmp_arg != NULL)
	//{
	//	printf("%s %d\n", tmp_arg->arg, tmp_arg->special);
	//	tmp_arg = tmp_arg->next;
	//}
	//while(args->head != NULL)
	//{
	//	tmp_arg = pop_head_arg(&args->head);
	//	free(tmp_arg->arg);
	//	free(tmp_arg);
	//}
	return (0);
}