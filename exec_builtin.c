/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:10:47 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 21:32:51 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one_builtin(t_info *info, t_cmd *cmd_line)
{
	if (handle_redirection(cmd_line->redirections) != ERROR)
		g_exit_code = exec_builtin(cmd_line->cmd_args, info->envs);
	free_cmd_node(&cmd_line);
	free(info->cmds);
	return (0);
}

int	isbuiltin(char **cmd_args)
{
	char	*cmd;

	if (cmd_args == NULL || *cmd_args == NULL)
		return (1);
	cmd = cmd_args[0];
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (1);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (1);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (1);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (1);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(char **cmd_line, t_env_deque *envs)
{
	int	exit_code;

	exit_code = 0;
	if (cmd_line[0] == NULL)
		return (0);
	if (ft_strncmp("echo", cmd_line[0], 5) == 0)
		exit_code = ft_echo(cmd_line);
	else if (ft_strncmp("cd", cmd_line[0], 3) == 0)
		exit_code = ft_cd(cmd_line, envs);
	else if (ft_strncmp("pwd", cmd_line[0], 4) == 0)
		exit_code = ft_pwd(envs);
	else if (ft_strncmp("export", cmd_line[0], 7) == 0)
		exit_code = ft_export(cmd_line, envs);
	else if (ft_strncmp("unset", cmd_line[0], 6) == 0)
		exit_code = ft_unset(cmd_line, envs);
	else if (ft_strncmp("env", cmd_line[0], 4) == 0)
		exit_code = ft_env(cmd_line, envs);
	else if (ft_strncmp("exit", cmd_line[0], 5) == 0)
		ft_exit(cmd_line);
	return (exit_code);
}
