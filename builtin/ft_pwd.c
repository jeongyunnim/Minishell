/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:41:13 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/22 15:41:34 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//char	*ft_oldpwd(t_env_deque *envs)
//{
//	char	*tmp;
//	t_env	*target;
//
////	tmp = getcwd(NULL, 0);
////	if (tmp == NULL)
//	target = find_target("PWD", envs);
//	if (!target || target->value == NULL)
//	{
//		tmp = getcwd(NULL, 0);
//		if (tmp == NULL)
//			return (0);
//	}
//	tmp = ft_strdup(target->value);
//	return (tmp);
//}

char	*ft_oldpwd(t_env_deque *envs)
{
	char	*tmp;
	t_env	*target;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		target = find_target("PWD", envs);
		if (!target || target->value == NULL)
			return (0);
		tmp = ft_strdup(target->value);
	}
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
		free(tmp);
		return (0);
	}
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}
