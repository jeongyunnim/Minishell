/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:10 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/22 15:48:20 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	tmp = (t_env_deque *) malloc(sizeof(t_env_deque));
	if (tmp == NULL)
		return (NULL);
	tmp->head = NULL;
	tmp->tail = NULL;
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

void	ft_env(char **argv, t_env_deque *envs)
{
	t_env	*env;
	char	*name;
	char	*value;

	env = envs->head;
	if (argv[1] == NULL)
	{
		while (env != NULL)
		{
			name = env->name;
			value = env->value;
			if (value == NULL)
			{
				env = env->next;
				continue ;
			}
			printf("%s=%s\n", name, value);
			env = env->next;
		}
	}
	else
		print_builtin_error("env", argv[1]);
}
