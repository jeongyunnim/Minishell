/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:10 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/26 15:13:12 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*find_target(char *str, t_env_deque *envs)
{
	t_env	*target;

	target = envs->head;
	while (target != NULL)
	{
		if (ft_strncmp(str, target->name, ft_strlen(str) + 1) == 0)
			return (target);
		target = target->next;
	}
	return (0);
}

t_env_deque	*dup_env(t_env_deque *envs)
{
	t_env_deque	*tmp;
	t_env		*env;
	t_env		*new;

	tmp = (t_env_deque *)ft_calloc(sizeof(t_env_deque), 1);
	env = envs->head;
	while (env != NULL)
	{
		new = lstnew_env();
		new->name = ft_strdup(env->name);
		if (env->value != NULL)
			new->value = ft_strdup(env->value);
		append_tail_env(&tmp->head, &tmp->tail, new);
		new = NULL;
		env = env->next;
	}
	return (tmp);
}

int	ft_env(char **argv, t_env_deque *envs)
{
	t_env	*env;

	env = envs->head;
	if (argv[1] == NULL)
	{
		while (env != NULL)
		{
			if (env->value != NULL)
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	else
	{
		print_builtin_error("env", argv[1]);
		return (127);
	}
	return (0);
}
