/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:39:41 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/26 18:09:23 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_builtin_error(char *arg, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (ft_strcmp(arg, "cd") == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (ft_strcmp(arg, "env") == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (ft_strcmp(arg, "exit") == 0)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
}

void	fail_getcwd(t_env_deque *envs, char *path, char *oldpwd)
{
	t_env	*target;
	char	*pwd;
	char	*tmp;

	target = find_target("PWD", envs);
	if (!target)
		return ;
	tmp = ft_strjoin(target->value, "/");
	pwd = ft_strjoin(tmp, path);
	free (tmp);
	if (oldpwd == 0)
		oldpwd = ft_strdup(target->value);
	change_env(envs, "OLDPWD", oldpwd);
	change_env(envs, "PWD", pwd);
	free(oldpwd);
	free(pwd);
}

void	free_three_string(char *s1, char *s2, char *s3)
{
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	if (s3 != NULL)
		free(s3);
}
