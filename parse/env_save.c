/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:03:58 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 15:11:28 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_deque	*save_env(char *env[])
{
	t_env_deque		*envs;
	t_env			*new;
	unsigned int	i;
	unsigned int	name_len;

	i = -1;
	envs = (t_env_deque *)ft_calloc(1, sizeof(t_env_deque));
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
			continue ;
		new = lstnew_env();
		name_len = ft_strchr(env[i], '=') - env[i];
		new->name = ft_calloc(name_len + 1, sizeof(char));
		ft_strlcpy(new->name, env[i], name_len + 1);
		if (*(env[i] + name_len) != '\0')
		{
			new->value = ft_strdup(env[i] + name_len + 1);
			new->value_len = ft_strlen(new->value);
		}
		new->name_len = name_len;
		append_tail_env(&envs->head, &envs->tail, new);
	}
	return (envs);
}
