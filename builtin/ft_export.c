/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:48:58 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/26 15:13:12 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_export(char **argv, t_env_deque *envs)
{
	char	*name;
	char	*value;
	int		i;

	i = 1;
	while (argv[i] != NULL)
	{
		name = argv[i];
		if (*(argv[i]) != '=')
			value = ft_strchr(argv[i], '=');
		if (check_export_name(name) == 0)
		{
			if (value != NULL)
				*value = '\0';
			if (value == NULL)
				find_env(envs, name, value);
			else
				find_env(envs, name, value + 1);
		}
		i++;
	}
}

void	print_export(t_env_deque *sort)
{
	t_env	*env;
	char	*name;
	char	*value;

	env = sort->head;
	while (env != NULL)
	{
		name = env->name;
		value = env->value;
		if (value == NULL)
			printf("declare -x %s\n", name);
		else
		{
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		env = env->next;
	}
}

void	swap_list(t_env *a, t_env *b)
{
	char	*name;
	char	*value;

	name = a->name;
	a->name = b->name;
	b->name = name;
	value = a->value;
	a->value = b->value;
	b->value = value;
}

t_env_deque	*sort_env(t_env_deque *envs)
{
	t_env_deque	*tmp_deque;
	t_env		*tmp;
	t_env		*tmp2;

	tmp_deque = dup_env(envs);
	tmp = tmp_deque->head;
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		while (tmp2 != NULL)
		{
			if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name) + 1) > 0)
				swap_list(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (tmp_deque);
}

int	ft_export(char **argv, t_env_deque *envs)
{
	t_env_deque	*sort;

	if (argv[1] == NULL)
	{
		sort = sort_env(envs);
		print_export(sort);
		free_env_deque(&sort);
		return (0);
	}
	set_export(argv, envs);
	return (0);
}
