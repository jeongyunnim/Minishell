/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/05 19:39:11 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(int c)
{
	if(c == '\'' || c == '\"')
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
	{
		return (0);
	}
}

int	count_arg_len(char *input, t_env_deque *envs)
{
	unsigned int	cnt;
	unsigned int	i;
	char			quote_flag;

	cnt = 0;
	i = 0;
	quote_flag = 0;
	while (input[i] != '\0') // return 조건 추가하기
	{
		if (quote_flag == 0 && ft_isspace(input[i]) == 1)
			return (cnt);
		else if (is_quote(input[i]) == 1)
			cnt += enter_quote(input[i], &quote_flag);
		else if (quote_flag != 1 && input[i] == '$')
		{
			cnt += set_env_len(input, &i, envs, quote_flag);
            if (input[i] == '\0')
                break ;
		}
		else if (quote_flag == 0 && ft_ismeta(input[i]) == 1)
			return (meta_len(input));
		else
			cnt++;
		i++;
		if (quote_flag == 0 && ft_ismeta(input[i]) == 1)
			return (cnt);
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

	args = (t_arg_deque *)ft_calloc(1, sizeof(t_arg_deque));
	if (args == NULL)
		return (ERROR);
	info->arguments = args;
	while (*input != '\0')
	{
		arg = NULL;
		special = 0;
		while (*input != '\0' && ft_isspace(*input) != 0)
		{
			input++;
		}
		if (*input != '\0')
		{
			arg_len = count_arg_len(input, info->envs);
			printf("arg_len: %d\n", arg_len);
			if (arg_len == ERROR)
				return (ERROR);
			else if (arg_len != 0 || is_quote(*input) == 1)
			{
				arg = (char *)ft_calloc(arg_len + 1, sizeof(char));
				if (arg == NULL)
					return (ERROR);
			}
			special = save_arg(&input, arg, arg_len, info->envs);
			if (arg != NULL)
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