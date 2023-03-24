/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyecheon <hyecheon@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:12:25 by hyecheon          #+#    #+#             */
/*   Updated: 2023/03/22 16:12:34 by hyecheon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env(t_env_deque *envs, char *name, char *value)
{
	t_env	*target;

	target = find_target(name, envs);
	if (target == 0 || target == NULL)
		add_export_env(envs, name, value);
	else
		update_env(target, value);
}

int	change_dir(char *path, t_env_deque *envs)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = ft_oldpwd(envs);
	if (chdir(path) == -1)
	{
		print_builtin_error("cd", path);
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_builtin_error("cd", path);
		fail_getcwd(envs, path, oldpwd);
		free(pwd);
		return (1);
	}
	change_env(envs, "OLDPWD", oldpwd);
	change_env(envs, "PWD", pwd);
	free(pwd);
	free(oldpwd);
	return (0);
}

int	ft_cd_oldpwd(t_env_deque *envs)
{
	char	*path;
	int		ret_flag;
	t_env	*target;

	target = find_target("OLDPWD", envs);
	if (target == 0 || target->value == NULL)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	else
	{
		path = ft_strdup(target->value);
		if (change_dir(path, envs) == 0)
		{
			printf ("%s\n", path);
			ret_flag = 0;
		}
		else
			ret_flag = 1;
	}
	free(path);
	return (ret_flag);
}

int	ft_cd_home(t_env *target, t_env_deque *envs)
{
	char	*path;

	if (target == 0 || target->value == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	else if (target->value != NULL && target->value[0] == '\0')
		return (0);
	else
		path = ft_strdup(target->value);
	change_dir(path, envs);
	free(path);
	return (0);
}

int	ft_cd(char **argv, t_env_deque *envs)
{
	char	*path;
	t_env	*target;
	int		ret_flag;

	if (argv[1] == NULL)
	{
		target = find_target("HOME", envs);
		return (ft_cd_home(target, envs));
	}
	else if (*(argv[1]) == '\0')
		return (0);
	else if (*(argv[1]) == '-')
		return (ft_cd_oldpwd(envs));
	else
		path = ft_strdup(argv[1]);
	if (change_dir(path, envs) == 0)
		ret_flag = 0;
	else
		ret_flag = 1;
	free(path);
	return (ret_flag);
}
