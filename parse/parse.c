/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/26 17:16:25 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_home_path(t_info *info, char **arg)
{
	t_env	*move;

	free(*arg);
	move = find_target("HOME", info->envs);
	if (move != NULL && move->value != NULL)
		*arg = ft_strdup(move->value);
	else
	{
		if (info->home_dir == NULL)
			*arg = ft_strdup("");
		else
			*arg = ft_strdup(info->home_dir);
	}
}

void	replace_home_cat_path(t_info *info, char **arg)
{
	t_env	*move;
	char	*home_directory;
	char	*dir_temp;

	move = find_target("HOME", info->envs);
	if (move != NULL && move->value != NULL)
		home_directory = ft_strdup(move->value);
	else
	{
		if (info->home_dir == NULL)
			home_directory = ft_strdup("");
		else
			home_directory = ft_strdup(info->home_dir);
	}
	dir_temp = ft_strdup(*arg + 1);
	free(*arg);
	*arg = ft_strjoin(home_directory, dir_temp);
	free(home_directory);
	free(dir_temp);
}

void	handle_input(t_info *info, char **input, char **arg)
{
	char	special;

	special = save_arg(input, *arg, info->envs);
	if (*arg == NULL)
		return ;
	if (**arg == '~' && *(*arg + 1) == '\0')
		replace_home_path(info, arg);
	else if (**arg == '~' && *(*arg + 1) == '/')
		replace_home_cat_path(info, arg);
	arg_to_deque(&info->arguments, *arg, special);
	free(*arg);
}

int	parse(char *input, t_info *info)
{
	t_parse_index	index;
	t_arg_deque		*args;
	char			*arg;
	int				arg_len;

	args = (t_arg_deque *)ft_calloc(1, sizeof(t_arg_deque));
	info->arguments = args;
	while (*input != '\0')
	{
		arg = NULL;
		while (*input != '\0' && ft_isspace(*input) != 0)
			input++;
		if (*input != '\0')
		{
			ft_memset(&index, 0, sizeof(index));
			arg_len = count_arg_len(input, index, info->envs);
			if (arg_len < 0)
				return (arg_len);
			else if (arg_len != 0 || (arg_len == 0 && is_quote(*input) == 1))
				arg = (char *)ft_calloc(arg_len + 1, sizeof(char));
			handle_input(info, &input, &arg);
		}
	}
	return (arg_len);
}
