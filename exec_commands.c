/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:53:12 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 16:39:33 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(char **argv, int i)
{
	if (argv[i] == NULL)
		printf("");
	else
		printf("%s", argv[i]);
	if (argv[i] && argv[i + 1] != NULL)
		printf(" ");
}

int	check_echo_flag(char *str)
{
	int	i;

	if (str != NULL)
	{
		if (str[0] == '-')
		{
			i = 1;
			while (str[i] != '\0')
			{
				if (str[i] != 'n')
					return (0);
				i++;
			}
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;
	int	n_flag;
	int	cnt;

	i = 1;
	cnt = 0;
	n_flag = (check_echo_flag(argv[1]));
	while (argv[i] != NULL)
	{
		if (n_flag == 1)
		{
			i++;
			cnt++;
			while (argv[i] != NULL && check_echo_flag(argv[i]) != 0)
				i++;
			n_flag = 0;
		}
		print_echo(argv, i);
		if (argv[i] == NULL)
			break ;
		i++;
	}
	if (cnt == 0)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("getcwd error");
		free(tmp);
		return (EXIT_FAILURE);
	}
	printf("%s\n", tmp);
	free(tmp);
	return (EXIT_SUCCESS);
}

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **argv)
{
	int	tmp;

	if (argv[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (argv[2] != NULL)
		printf("minishell: exit: too many arguments\n");
	else if (argv[1] != NULL)
	{
		if (check_numeric(argv[1]) != 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			exit (255);
		}
		tmp = ft_atoi(argv[1]);
		printf("exit\n");
		exit(tmp);
	}
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
		printf("minishell: env: %s: No such file or directory\n", argv[1]);
}

void	swap_data(t_env *a, t_env *b)
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

t_env_deque	*sort_env(t_env_deque *envs)
{
	t_env_deque	*tmp_deque;
	t_env		*tmp;
	t_env		*tmp2;

	tmp_deque = dup_env(envs);
	tmp = tmp_deque->head;
	if (tmp == NULL && tmp->name == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		tmp2 = tmp->next;
		while (tmp2 != NULL)
		{
			if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name) + 1) > 0)
				swap_data(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (tmp_deque);
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

int	check_export_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
		return (0);
	}
	while (str[i] != '\0')
	{
		if (i != 0 && str[i] == '=')
			return (1);
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

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

void	ft_export(char **argv, t_env_deque *envs)
{
	t_env_deque	*sort;
	char		*name;
	char		*value;
	int			i;

	if (argv[1] == NULL)
	{
		sort = sort_env(envs);
		if (!sort->head)
			return ;
		print_export(sort);
		free_env_deque(&sort);
		return ;
	}
	i = 1;
	while (argv[i] != NULL)
	{
		name = argv[i];
		value = ft_strchr(argv[i], '=');
		if (value != NULL)
			*value = '\0';
		if (!check_export_name(name))
			return ;
		if (value == NULL)
			find_env(envs, name, value);
		else
			find_env(envs, name, value + 1);
		i++;
	}
}

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

void	del_env(t_env **head, t_env **tail, t_env *target)
{
	if (target == NULL)
		return ;
	if (*head == target)
		*head = target->next;
	if (*tail == target)
		*tail = target->previous;
	if (target->previous != NULL)
		target->previous->next = target->next;
	if (target->next != NULL)
		target->next->previous = target->previous;
	free(target->name);
	free(target->value);
	free(target);
}

int	check_unset_valid(char *str)
{
	int	i;

	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char **argv, t_env_deque *envs)
{
	int		i;
	t_env	*target;

	i = 1;
	while (argv[i] != NULL)
	{
		if (!check_unset_valid(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("' not a valid identifier", STDERR_FILENO);
			return ;
		}
		target = find_target(argv[i], envs);
		del_env(&envs->head, &envs->tail, target);
		i++;
	}
}

void	change_env(t_env_deque *envs, char *name, char *value)
{
	t_env	*target;

	target = find_target(name, envs);
	if (target == 0 || target == NULL)
		add_export_env(envs, name, value);
	else
		update_env(target, value);
}

//free return 함수 만들어서 줄수 줄이기
int	change_dir(char *path, t_env_deque *envs)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("minishell: cd : %s:no such file or directory\n", path);
		return (EXIT_FAILURE);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("getcwd error");
			free(pwd);
			return (EXIT_FAILURE);
		}
		change_env(envs, "OLDPWD", oldpwd);
		change_env(envs, "PWD", pwd);
		free(pwd);
	}
	free(oldpwd);
	return (EXIT_SUCCESS);
}

int	ft_cd_oldpwd(t_env_deque *envs)
{
	char	*path;
	t_env	*target;

	target = find_target("OLDPWD", envs);
	if (target == 0 || target->value == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	else
	{
		path = ft_strdup(target->value);
		if (change_dir(path, envs) == EXIT_SUCCESS)
			printf ("%s\n", path);
	}
	free(path);
	return (0);
}

int	ft_cd_home(t_env *target, t_env_deque *envs, char *str)
{
	char	*path;

	if (str == NULL)
	{
		if (target == 0 || target->value == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		else if (target->value != NULL && target->value[0] == '\0')
			return (0);
		else
			path = ft_strdup(target->value);
	}
	change_dir(path, envs);
	free(path);
	return (0);
}

int	ft_cd(char **argv, t_env_deque *envs)
{
	char	*path;
	t_env	*target;

	target = find_target("HOME", envs);
	if (argv[1] == NULL)
	{
		ft_cd_home(target, envs, argv[1]);
		return (0);
	}
	else if (*(argv[1]) == '\0')
		return (0);
	else if (*(argv[1]) == '-')
	{
		ft_cd_oldpwd(envs);
		return (0);
	}
	else
		path = ft_strdup(argv[1]);
	change_dir(path, envs);
	free(path);
	return (0);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

char	*gen_temp_file_name(int flag)
{
	static char		name[8];
	static int		i;

	if (flag == 0)
	{
		i = 0;
		return (NULL);
	}
	if (i == 0 || i == 16)
	{
		ft_memcpy(name, "temp/", 5);
		i = 0;
	}
	if (i > 9)
	{
		name[5] = '1';
		name[6] = i - 10 + '0';
	}
	else
	{
		name[5] = i + '0';
		name[6] = '\0';
	}
	i++;
	return (name);
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

void	parent_process_wait(t_info *info, pid_t pid, int pipes)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i <= pipes)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFEXITED(status) == 1)
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 1)
		exited_by_signal(info, status);
}

int	exec_builtin(char **cmd_line, t_env_deque *envs)
{
	if (cmd_line[0] == NULL || cmd_line[0][0] == '\0')
		return (0);
	if (ft_strncmp("echo", cmd_line[0], 5) == 0)
		ft_echo(cmd_line);
	else if (ft_strncmp("cd", cmd_line[0], 3) == 0)
		ft_cd(cmd_line, envs);
	else if (ft_strncmp("pwd", cmd_line[0], 4) == 0)
		ft_pwd();
	else if (ft_strncmp("export", cmd_line[0], 7) == 0)
		ft_export(cmd_line, envs);
	else if (ft_strncmp("unset", cmd_line[0], 6) == 0)
		ft_unset(cmd_line, envs);
	else if (ft_strncmp("env", cmd_line[0], 4) == 0)
		ft_env(cmd_line, envs);
	else if (ft_strncmp("exit", cmd_line[0], 5) == 0)
		ft_exit(cmd_line);
	else
		return (1);
	return (0);
}

char	**envlist_to_arry(t_env_deque *envs)
{
	t_env	*env;
	char	**array;
	char	*temp;
	int		cnt;
	int		i;

	i = 0;
	env = envs->head;
	while (env != NULL)
	{
		cnt++;
		env = env->next;
	}
	array = (char **)ft_calloc(sizeof(char *), (cnt + 1));
	env = envs->head;
	while (env != NULL)
	{
		if (env->value != NULL)
		{
			temp = array[i];
			array[i] = ft_strjoin(env->name, "=");
			free(temp);
			temp = array[i];
			array[i] = ft_strjoin(array[i], env->value);
			free(temp);
		}
		env = env->next;
		i++;
	}
	return (array);
}

int	exec_one_builtin(t_info *info, t_cmd *cmd_line)
{
	if (handle_redirection(cmd_line->redirections) != ERROR)
		exec_builtin(cmd_line->cmd_args, info->envs);
	free_cmd_node(&cmd_line);
	free(info->cmds);
	return (0);
}

void	init_pipe_index(t_pipe_index *index, int flag)
{
	if (flag == 0)
	{
		index->fd[0] = -1;
		index->fd[1] = -1;
		index->prev_pipe_read = -1;
		index->i = 0;
		index->pid = 0;
	}
	else
	{
		if (index->prev_pipe_read != -1)
			close(index->prev_pipe_read);
		if (index->fd[1] != -1)
			close(index->fd[1]);
		index->prev_pipe_read = index->fd[0];
	}
}

void	parent_process_run(t_cmd **cmd_line, t_pipe_index *index, t_info *info)
{
	set_signal_mode(FORK_PARENT_M);
	free_cmd_node(cmd_line);
	*cmd_line = pop_head_cmd(&(info->cmds->head));
	init_pipe_index(index, 1);
}

int	fork_and_run(t_info *info, t_pipe_index *index, t_cmd **cmd_line)
{
	if (index->pid == -1)
		return (ERROR);
	else if (index->pid == 0)
		child_process_run(*cmd_line, *index, info);
	else
		parent_process_run(cmd_line, index, info);
	return (0);
}

int	exec_commands(t_info *info)
{
	t_cmd			*cmd_line;
	t_pipe_index	index;

	init_pipe_index(&index, 0);
	gen_temp_file_name(0);
	if (heredoc_handler(info) != 0)
		return (ERROR);
	cmd_line = pop_head_cmd(&info->cmds->head);
	while (cmd_line != NULL)
	{
		if (index.i < info->pipes)
		{
			if (pipe(index.fd) == ERROR)
				return (ERROR);
		}
		if (info->pipes == 0 && isbuiltin(cmd_line->cmd_args) == 1)
			return (exec_one_builtin(info, cmd_line));
		index.pid = fork();
		if (fork_and_run(info, &index, &cmd_line) == ERROR)
			return (ERROR);
		index.i += 1;
	}
	free(info->cmds);
	parent_process_wait(info, index.pid, info->pipes);
	return (0);
}

//exec_commands()에 부모가 기다리기 전에 자식이 끝나버리면 어쩌지?