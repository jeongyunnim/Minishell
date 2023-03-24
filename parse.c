/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:28:52 by jeseo             #+#    #+#             */
/*   Updated: 2023/03/24 18:43:02 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_home_path(t_info *info, char **arg)
{
	t_env	*move;

	free(*arg);
	move = info->envs->head;
	while (move != NULL)
	{
		if (ft_strncmp(move->name, "HOME", 5) == 0)
			break ;
		move = move->next;
	}
	if (move != NULL && move->value != NULL)
	{
		*arg = ft_strdup(move->value);
	}
	else
	{
		if (info->home_dir == NULL)
			*arg = ft_strdup("");
		else
			*arg = ft_strdup(info->home_dir);
	}
}

void	handle_valid_input(t_info *info, char **input, char **arg, int arg_len)
{
	char	special;

	special = save_arg(input, *arg, arg_len, info->envs);
	if (ft_strncmp(*arg, "~", 2) == 0)
		replace_home_path(info, arg);
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
			if (arg != NULL)
				handle_valid_input(info, &input, &arg, arg_len);
		}
	}
	return (arg_len);
}
