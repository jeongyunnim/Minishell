/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:58 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/21 20:10:23 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_special(int c)
{
	if (c == '?' || c == '0' || c == '$')
		return (1);
	else
		return (0);
}

int	invalid_env_name(char *input, unsigned int *i)
{
	int	special;

	special = 0;
	if (ft_isdigit(input[*i]) != 0)
		(*i)++;
	else if (ft_isalnum(input[*i]) == 1 || input[*i] == '_')
	{
		while (ft_isalnum(input[*i]) == 1 || input[*i] == '_')
			(*i)++;
	}
	else
		special = 1;
	return (special);
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
		len++;
	while (temp != NULL)
	{
		if (len == temp->name_len && \
			ft_strncmp(&input[*i], temp->name, len) == 0)
		{
			(*i) += len;
			return (temp->value_len);
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

	i = -1;
	envs = (t_env_deque *)ft_calloc(1, sizeof(t_env_deque));
	if (envs == NULL)
		return (NULL);
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
			continue ;
		new = lstnew_env();
		name_len = ft_strchr(env[i], '=') - env[i];
		if (name_len == 0)
			return (NULL);
		new->name = ft_calloc(name_len + 1, sizeof(char));
		ft_strlcpy(new->name, env[i], name_len + 1);
		if (*(env[i] + name_len) != '\0' && ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			new->value = ft_strdup(env[i] + name_len + 1);
			new->value_len = ft_strlen(new->value);
		}
		new->name_len = name_len;
		append_tail_env(&envs->head, &envs->tail, new);
	}
	return (envs);
}

int	set_env_len(char *input, unsigned int *i, t_env_deque *env, char qflag)
{
	int	cnt;

	cnt = 0;
	(*i)++;
	if (input[*i] == '\0' || ft_isspace(input[*i]) == 1 \
		|| (is_quote(input[*i]) == 1 && qflag != 0))
			return (1);
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

int	 valid_env_name_replace(char **input, char **arg, t_env_deque *env)
{
	t_env			*temp;
	unsigned int	i;

	temp = env->head;
	i = 0;
	if (is_env_special(**input) == 1)
	{
		env_special_replace(input, arg);
		return (0);
	}
	while (ft_isalnum((*input)[i]) == 1 || (*input)[i] == '_')
		i++;
	while (temp != NULL)
	{
		if (i == temp->name_len && ft_strncmp((*input), temp->name, i) == 0)
		{
			ft_memcpy(*arg, temp->value, temp->value_len);
			(*input) += temp->name_len;
			(*arg) += temp->value_len;
			return (0);
		}
		temp = temp->next;
	}
	(*input) += i;
	return (0);
}
