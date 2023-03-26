/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_valid_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:22:33 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_env_name_replace(char **input, char **arg, t_env_deque *env)
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
