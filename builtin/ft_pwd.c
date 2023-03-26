/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:41:13 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/26 18:31:57 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_oldpwd(t_env_deque *envs)
{
	char	*tmp;
	t_env	*target;

	target = find_target("PWD", envs);
	if (target)
		tmp = ft_strdup(target->value);
	else
		return (NULL);
	return (tmp);
}

int	ft_pwd(t_env_deque *envs)
{
	char	*tmp;
	t_env	*target;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		target = find_target("PWD", envs);
		if (!target)
			return (0);
		printf("%s\n", target->value);
		return (0);
	}
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}
