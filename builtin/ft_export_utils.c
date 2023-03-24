/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:56:04 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/22 15:56:07 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_export_env(t_env_deque *envs, char *name, char *value)
{
	t_env	*new;

	new = lstnew_env();
	new->name = ft_strdup(name);
	new->name_len = ft_strlen(new->name);
	if (value != NULL)
	{
		new->value = ft_strdup(value);
		new->value_len = ft_strlen(new->value);
	}
	append_tail_env(&envs->head, &envs->tail, new);
}

void	update_env(t_env *env, char *value)
{
	char	*new_value;

	if (value == NULL)
	{
		free(env->value);
		env->value_len = 0;
		env->value = NULL;
	}
	else
	{
		new_value = ft_strdup(value);
		free(env->value);
		env->value = new_value;
		env->value_len = ft_strlen(new_value);
	}
}

int	find_env(t_env_deque *envs, char *name, char *value)
{
	t_env	*env;

	env = envs->head;
	while (env != NULL)
	{
		if (ft_strncmp(name, env->name, env->name_len + 1) == 0)
		{
			if (value != NULL)
				update_env(env, value);
			return (0);
		}
		env = env->next;
	}
	add_export_env(envs, name, value);
	return (0);
}

int	check_export_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	while (str[i] != '\0')
	{
		if (i != 0 && str[i] == '=')
			return (0);
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
	}
	return (0);
}
