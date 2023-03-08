/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:58 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/07 16:41:25 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_special(int c)
{
	if (c == '?' || c == '0') // _, -, !는 처리할 수가 없다. 마지막 인자를 어떻게 가지고 다녀?
		return (1);
	else
		return (0);
}

int	invalid_env_name(char *input, unsigned int *i)
{
	if (ft_isdigit(input[*i]) != 0)
	{ 
		(*i)++;
	}
	else
	{
		while (ft_isalnum(input[*i]) == 1 || input[*i] == '_')
		{
			(*i)++;
		}
	}
	return (0);
}

int	valid_env_name_match(char *input, t_env_deque *env, unsigned int *i)
{
	t_env			*temp;
	unsigned int	len;

	temp = env->head;
	len = 0;
	if (is_env_special(input[*i]) == 1)
	{
		len = env_special_len(&input[*i]);
		(*i)++;
		return (len);
	}
	while (ft_isalnum(input[*i + len]) == 1 || input[*i + len] == '_')
	{
		len++;
	}
	while (temp != NULL)
	{
		if (len == temp->name_len)
		{
			if (ft_strncmp(&input[*i], temp->name, len) == 0)
			{
                (*i) += len;
				return (temp->value_len);
			}
		}
		temp = temp->next;
	}
    (*i) += len;
	return (0);
}

t_env_deque	*save_env(char *env[])
{
	unsigned int	i;
	unsigned int	name_len;
	t_env_deque		*envs;
	t_env			*new;

	i = 0;
	envs = (t_env_deque *)ft_calloc(1, sizeof(t_env_deque));
	if (envs == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		new = lstnew_env();
		name_len = ft_strchr(env[i], '=') - env[i];
		if (name_len == 0)
		{
			return (NULL);
		}
		new->name = ft_calloc(name_len + 1, sizeof(char));
		if (new->name == NULL)
		{
			return (NULL);
		}
		ft_strlcpy(new->name, env[i], name_len + 1);
		if (*(env[i] + name_len )!= '\0')
		{
			new->value = ft_strdup(env[i] + name_len + 1);
			if (new->value == NULL)
			{
				return (NULL);
			}
		}
		new->name_len = name_len;
		new->value_len = ft_strlen(env[i] + name_len + 1);
		append_tail_env(&envs->head, &envs->tail, new);
		new = NULL;
		i++;
	}
	return (envs);
}

int	set_env_len(char *input, unsigned int *i, t_env_deque *env, char quote_flag)
{
	int	cnt;

	cnt = 0;
	(*i)++;
	if (ft_isspace(input[*i]) == 1 || input[*i] == '\0' || input[*i] == '$')
	{
        (*i)--;
        return (1); // $ 하나만 왔으므로 $표시.
	}
	else if (is_quote(input[*i]) == 1)
	{
        (*i)--;
        if (quote_flag != 0) // 쿼트 내부에서 짝이 없는 $는 $표시
			return (1);
		return (0);
	}
	else if (ft_isupper(input[*i]) == 1 || is_env_special(input[*i]) == 1 || input[*i] == '_')
	{
		cnt = valid_env_name_match(input, env, i);
		(*i)--;
		return (cnt);
	}
	else
	{
		invalid_env_name(input, i);
		(*i)--;
		return (0);
	}
}

int	 valid_env_name_replace(char **input, char **arg, t_env_deque *env)
{
	t_env	*temp;
	unsigned int i;

	temp = env->head;
	i = 0;
	if (is_env_special(**input) == 1)
	{
		env_special_replace(input, arg);
		return (0);
	}
	while (ft_isalnum((*input)[i]) == 1 || (*input)[i] == '_')
	{
		i++;
	}
	while (temp != NULL)
	{
		if (i == temp->name_len)
		{
			if (ft_strncmp((*input), temp->name, i) == 0)
			{
				ft_memcpy(*arg, temp->value, temp->value_len);
				(*input) += temp->name_len;
				(*arg) += temp->value_len;
				return (0);
			}
		}
		temp = temp->next;
	}
	(*input) += i;
	return (0);
}

int	replace_env(char **input, char **arg, t_env_deque *env, char quote_flag)
{	
	unsigned int	i;

	i = 0;
	(*input)++;
	if (ft_isspace(**input) == 1 || **input == '\0' || **input == '$')
	{
		**arg = '$';
		(*arg)++;
		return (0);
	}
	else if (is_quote(**input) == 1)
	{
		if (quote_flag != 0)
		{
			**arg = '$';
			(*arg)++;
		}
		return (0);
	}
	else if (ft_isupper(**input) == 1 || is_env_special(**input) == 1 || **input == '_')
	{
		valid_env_name_replace(input, arg, env);
	}
	else
	{
		invalid_env_name(*input, &i);
		(*input) += i;
	}
    (*input)--;
	return (0);
}
