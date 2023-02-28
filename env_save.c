/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:58 by jeseo             #+#    #+#             */
/*   Updated: 2023/02/28 17:41:58 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspecial_parameter(int c)
{
	if (c == '$' || c == '?' || c == '-' || c == '_' || c == '0' || c == '!')
		return (1);
	else
		return (0);
}

int	invalid_env_name(char *input)
{
	unsigned int	i;

	i = 0;
	if (ft_isdigit(input[i]) != 0)
	{
		i++;
	}
	else
	{
		while (ft_isalnum(input[i]) == 1 || input[i] == '_')
		{
			i++;
		}
	}
	return (i);
}

int	valid_env_name_find(char *input, t_env_deque *env, unsigned int *cnt)
{
	t_env	*temp;
	unsigned int i;

	temp = env->head;
	i = 0;
	while (ft_isalnum(input[i]) == 1 || input[i] == '_')
	{
		i++;
	}
	if (ft_isspecial_parameter(input[i]) == 1) // i가 하나일 때만???
	{
		printf(" | %c처리 coming soon. | ", input[i]);
		//특수 문자 처리
	}
	while (temp != NULL)
	{
		if (i == temp->name_len)
		{
			if (ft_strncmp(input, temp->name, i - 1) == 0)
			{
				*cnt += temp->value_len;
				return (i);
			}
		}
		temp = temp->next;
	}
	return (i);
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

int	set_env_len(char *input, unsigned int *cnt, t_env_deque *env)
{
	unsigned int len;

	len = 0;
	if (ft_isupper(input[len]) == 0 && ft_isspecial_parameter(input[len]) == 0)
	{
		len = invalid_env_name(input);
	}
	else
	{
		len = valid_env_name_find(input, env, cnt);
	}
	return (len);
}

int	valid_env_name_replace(char **input, char **arg, t_env_deque *env)
{
	t_env	*temp;
	unsigned int i;

	temp = env->head;
	i = 0;
	while (ft_isalnum((*input)[i]) == 1 || (*input)[i] == '_')
	{
		i++;
	}
	while (temp != NULL)
	{
		if (i == temp->name_len)
		{
			if (ft_strncmp((*input), temp->name, i - 1) == 0)
			{
				i = 0;
				while (i < temp->value_len)
				{
					**arg = (temp->value)[i];
					(*arg)++;
					i++;
				}
				*arg += temp->value_len;
				return (0);
			}
		}
		temp = temp->next;
	}
	(*input) += i;
}

void	replace_env(char **input, char **arg, t_env_deque *env)
{


	if (ft_isupper(**input) == 0 && ft_isspecial_parameter(**input) == 0)
	{
		(*input) += invalid_env_name(*input);
	}
	else
	{
		valid_env_name_replace(input, arg, env);
	}
	return ;
}
